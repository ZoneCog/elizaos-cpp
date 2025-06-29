from langchain_ollama import ChatOllama
import dateutil.parser
from typing import Dict, List, Any, Literal
import signal
import sys
import argparse
import json
import os
from collections import defaultdict
import logging
from rich.console import Console
from rich.progress import Progress, SpinnerColumn, TextColumn, BarColumn, TaskProgressColumn, TimeRemainingColumn
from rich.panel import Panel
from rich.table import Table
from datetime import datetime
from pydantic import BaseModel, Field

# Initialize rich console
console = Console()
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

def signal_handler(sig, frame):
    """Handle graceful shutdown on CTRL+C"""
    console.print("\n[yellow]Shutting down gracefully...[/]")
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

# Define structured output models
class ChatQuestion(BaseModel):
    question: str
    asker: str

class ChatHelp(BaseModel):
    helper: str
    recipient: str
    task: str
    assistance: str

class ActionItem(BaseModel):
    description: str
    mentioned_by: str
    type: Literal["Technical Tasks", "Documentation Needs", "Feature Requests"]

# Update the ChatAnalysis model with length constraints
class ChatAnalysis(BaseModel):
    summary: str = Field(..., max_length=1000)
    faq: List[ChatQuestion] = Field(..., max_items=20)
    help_interactions: List[ChatHelp] = Field(..., max_items=10)
    action_items: List[ActionItem] = Field(..., max_items=20)

def _merge_analyses(self, analyses: List[ChatAnalysis]) -> ChatAnalysis:
    """Merge multiple chunk analyses while enforcing strict limits"""
    seen_questions = set()
    seen_help = set()
    seen_actions = set()
    
    # Take the first summary as the base and append unique key points from others
    summaries = [a.summary for a in analyses if a.summary]
    base_summary = summaries[0] if summaries else ""
    
    merged = ChatAnalysis(
        # Truncate final summary if needed
        summary=base_summary[:1000],
        faq=[],
        help_interactions=[],
        action_items=[]
    )
    
    # Only take top items from each category
    for analysis in analyses:
        # Add unique FAQ items (up to max 20)
        for q in analysis.faq:
            key = f"{q.question}:{q.asker}"
            if key not in seen_questions and len(merged.faq) < 20:
                seen_questions.add(key)
                merged.faq.append(q)
        
        # Add unique help interactions (up to max 10)
        for h in analysis.help_interactions:
            key = f"{h.helper}:{h.recipient}:{h.task}"
            if key not in seen_help and len(merged.help_interactions) < 10:
                seen_help.add(key)
                merged.help_interactions.append(h)
        
        # Add unique action items (up to max 20)
        for a in analysis.action_items:
            key = f"{a.description}:{a.mentioned_by}"
            if key not in seen_actions and len(merged.action_items) < 20:
                seen_actions.add(key)
                merged.action_items.append(a)

    return merged

# Also update chunk size to be smaller
def _chunk_messages(self, messages: List[Dict[str, Any]], chunk_size: int = 5) -> List[List[Dict[str, Any]]]:
    """Split messages into smaller chunks for more focused analysis"""
    return [messages[i:i + chunk_size] for i in range(0, len(messages), chunk_size)]

class DiscordChatAnalyzer:
    def __init__(self, model_name='phi3-chat'):
        console.print(Panel.fit("[bold cyan]Initializing Discord Chat Analyzer[/]"))
        try:
            self.model = ChatOllama(
                model=model_name,
                temperature=0.2,
                num_ctx=4096,
                num_thread=24,
                num_gpu=-1,
                num_batch=512,
                repeat_penalty=1.2,
                num_keep=24
            )
            console.print("[green]✓[/] Model initialized successfully")
        except Exception as e:
            console.print(f"[bold red]Error initializing ChatOllama:[/] {e}")
            logger.info("Make sure Ollama is running and the model is downloaded")
            raise

    def format_structured_prompt(self, transcript: str) -> str:
        return f"""Analyze this Discord chat segment and provide a succinct analysis:
                
        1. Summary (max 500 words):
        - Focus ONLY on the most important technical discussions, decisions, and problem-solving
        - Highlight concrete solutions and implementations
        - Be specific and VERY concise
        
        2. FAQ (max 20 questions):
        - Only include the most significant questions that got meaningful responses
        - Focus on unique questions, skip similar or rhetorical questions
        - Include who asked the question and who answered
        - Use the exact Discord username from the chat
        
        3. Help Interactions (max 10):
        - List the significant instances where community members helped each other.
        - Be specific and concise about what kind of help was given
        - Include context about the problem that was solved
        - Mention if the help was successful
        
        4. Action Items (max 20 total):
        - Technical Tasks: Critical development tasks only
        - Documentation Needs: Essential doc updates only
        - Feature Requests: Major feature suggestions only

        For each action item, include:
        - Clear description
        - Who mentioned it
        
        Chat transcript:
        {transcript}
        
Return the analysis in the specified structured format. Be specific about technical content and avoid duplicating information."""


    def _analyze_chunk(self, chunk: List[Dict[str, Any]], users: Dict[str, Any], progress: Progress, chunk_task: int) -> ChatAnalysis:
        """Analyze a single chunk of messages with progress tracking"""
        transcript = self.format_messages(chunk, users)

        try:
            response = self.model.invoke(
                self.format_structured_prompt(transcript),
                format=ChatAnalysis.model_json_schema(),
            )
            
            analysis = ChatAnalysis.model_validate_json(response.content)
            progress.advance(chunk_task)
            return analysis

        except Exception as e:
            console.print(f"[red]Error analyzing chunk: {e}[/]")
            return ChatAnalysis(
                summary="",
                faq=[],
                help_interactions=[],
                action_items=[]
            )

    def format_messages(self, messages: List[Dict[str, Any]], users: Dict[str, Any]) -> str:
        """Format messages into readable text"""
        formatted = []
        for msg in messages:
            user = users.get(msg['uid'], {})
            username = user.get('nickname') or user.get('name', 'Unknown User')
            try:
                timestamp = dateutil.parser.parse(msg['ts']).strftime("%H:%M")
            except Exception:
                timestamp = msg['ts']
            content = msg.get('content', '')
            formatted.append(f"{username} ({timestamp}): {content}")
        return "\n".join(formatted)

    def _chunk_messages(self, messages: List[Dict[str, Any]], chunk_size: int = 20) -> List[List[Dict[str, Any]]]:
        """Split messages into chunks of specified size"""
        return [messages[i:i + chunk_size] for i in range(0, len(messages), chunk_size)]

    def _merge_analyses(self, analyses: List[ChatAnalysis]) -> ChatAnalysis:
        """Merge multiple chunk analyses while enforcing strict limits"""
        seen_questions = set()
        seen_help = set()
        seen_actions = set()
        
        # Use only first chunk's summary, limited to 1000 chars
        if analyses:
            base_summary = analyses[0].summary[:1000]
        else:
            base_summary = ""
            
        merged = ChatAnalysis(
            summary=base_summary,
            faq=[],
            help_interactions=[],
            action_items=[]
        )
        
        # Only take top items from each category
        for analysis in analyses:
            # Add unique FAQ items (up to max 10)
            for q in analysis.faq:
                key = f"{q.question}:{q.asker}"
                if key not in seen_questions and len(merged.faq) < 10:
                    seen_questions.add(key)
                    merged.faq.append(q)
            
            # Add unique help interactions (up to max 10)
            for h in analysis.help_interactions:
                key = f"{h.helper}:{h.recipient}:{h.task}"
                if key not in seen_help and len(merged.help_interactions) < 10:
                    seen_help.add(key)
                    merged.help_interactions.append(h)
            
            # Add unique action items (up to max 20)
            for a in analysis.action_items:
                key = f"{a.description}:{a.mentioned_by}"
                if key not in seen_actions and len(merged.action_items) < 20:
                    seen_actions.add(key)
                    merged.action_items.append(a)
        
        return merged


    def _format_markdown(self, analysis: ChatAnalysis, channel_name: str, date: str) -> str:
        """Format analysis as markdown"""
        sections = [
            f"# {channel_name} {date}\n",
            "## Summary",
            analysis.summary + "\n",
            "## FAQ",
            "\n".join(f"- {q.question} (asked by {q.asker})" for q in analysis.faq) + "\n",
            "## Who Helped Who",
            "\n".join(f"- {h.helper} helped {h.recipient} with {h.task} by providing {h.assistance}" 
                     for h in analysis.help_interactions) + "\n",
            "## Action Items"
        ]
        
        # Group action items by type
        action_types = {"Technical Tasks": [], "Documentation Needs": [], "Feature Requests": []}
        for action in analysis.action_items:
            action_types[action.type].append(f"- {action.description} (mentioned by {action.mentioned_by})")
        
        # Add action items by category
        for category, items in action_types.items():
            if items:
                sections.append(f"\n### {category}")
                sections.extend(items)
        
        return "\n".join(sections)

    def analyze_chat(self, chat_data: Dict[str, Any]) -> str:
        """Analyze Discord chat data with progress tracking"""
        start_time = datetime.now()
        messages = chat_data['messages']
        users = chat_data['users']
        
        # Display initial stats
        stats_table = Table(title="Chat Analysis Stats", show_header=False)
        stats_table.add_row("Total Messages", str(len(messages)))
        stats_table.add_row("Total Users", str(len(users)))
        console.print(stats_table)
        
        # Split into chunks and analyze
        chunks = self._chunk_messages(messages)
        analyses = []
        
        with Progress(
            SpinnerColumn(),
            TextColumn("[progress.description]{task.description}"),
            BarColumn(),
            TaskProgressColumn(),
            TimeRemainingColumn(),
            console=console
        ) as progress:
            task = progress.add_task("[cyan]Analyzing chat...", total=len(chunks))
            
            for chunk in chunks:
                analysis = self._analyze_chunk(chunk, users, progress, task)
                analyses.append(analysis)
        
        # Merge and format results
        merged_analysis = self._merge_analyses(analyses)
        final_output = self._format_markdown(
            merged_analysis,
            chat_data['channel']['name'],
            chat_data['date']
        )
        
        # Display completion stats
        elapsed_time = (datetime.now() - start_time).total_seconds()
        completion_table = Table(title="Analysis Complete!", show_header=False)
        completion_table.add_row("Time Elapsed", f"{elapsed_time:.2f} seconds")
        completion_table.add_row("Messages Processed", str(len(messages)))
        completion_table.add_row("Chunks Analyzed", str(len(chunks)))
        console.print(completion_table)
        
        return final_output

def main():
    """CLI interface for the Discord chat analyzer"""
    parser = argparse.ArgumentParser(description="Analyze Discord chat export data")
    parser.add_argument("-i", "--input", type=str, required=True,
                       help="Path to Discord chat export JSON file")
    parser.add_argument("-o", "--output", type=str, help="Path to save the output file")

    args = parser.parse_args()

    logger.info(f"Reading chat data from {args.input}")
    with open(args.input, 'r', encoding='utf-8') as f:
        chat_data = json.load(f)

    analyzer = DiscordChatAnalyzer()
    analysis = analyzer.analyze_chat(chat_data)

    if args.output:
        logger.info(f"Saving analysis to {args.output}")
        directory = os.path.dirname(args.output)
        if directory:
            os.makedirs(directory, exist_ok=True)
        with open(args.output, 'w', encoding='utf-8') as f:
            f.write(analysis)
        print(f"Analysis saved to {args.output}")
    else:
        print("\nAnalysis Results:")
        print(analysis)

if __name__ == "__main__":
    main()
