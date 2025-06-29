# Discord Chat Analyzer

A powerful Python script that analyzes Discord chat exports and generates comprehensive summaries using local LLM models through Ollama.

## Features

- **Smart Message Analysis**: Processes Discord chat exports and generates structured analysis including:
  - Concise technical discussion summaries
  - FAQ compilation from discussions 
  - Help interaction tracking
  - Action item extraction

- **Efficient Processing**:
  - Chunks messages for optimal processing
  - Uses local LLM models via Ollama
  - Progress tracking with rich CLI interface
  - Graceful shutdown handling

- **Structured Output**:
  - Markdown formatted reports
  - Categorized action items
  - Clear help interaction summaries
  - FAQ compilation

## Prerequisites

- Python 3.8+
- [Ollama](https://ollama.ai/) installed and running
  - https://ollama.com/download
- Required Python packages:
  ```
  langchain_ollama
  python-dateutil
  rich
  pydantic
  ```

## Installation

1. Clone the repository or download the script
2. Install required packages:

```bash
pip install langchain_ollama python-dateutil rich pydantic
```
3. Ensure Ollama is installed and running with a compatible model (default: phi3-chat)

The Modelfile is configured for a Linux system. Edit the Modelfile for your system: https://github.com/ollama/ollama/blob/main/docs/modelfile.md

```bash
# Pull whatever model you want to use, phi3 worked best in our tests for summarizing
ollama run phi3:14b-medium-4k-instruct-q5_K_M

# Edit the Modelfile first for your system
ollama create phi3-chat -f Modelfile 
```

> Note: For exporting Discord Chats you can look into using the Discord API and make a bot. Code soon.
> If using [DiscordChatExporter](https://github.com/Tyrrrz/DiscordChatExporter) a preprocess script is provided to make a more compact version of the JSON file to save on tokens

## Usage

Basic usage:
```bash
python summarize.py -i samples/chat_export.json -o /path/to/output.md
```

Arguments:
- `-i, --input`: Path to Discord chat export JSON file (required)
- `-o, --output`: Path to save the analysis output file (optional)

If no output path is specified, the analysis will be printed to stdout.

## Output Format

The script generates a structured markdown report containing:

1. **Summary**: Focused technical discussion overview
2. **FAQ**: Important questions and answers from the chat
3. **Help Interactions**: Tracking of community support
4. **Action Items**: Categorized into:
   - Technical Tasks
   - Documentation Needs
   - Feature Requests

> Note: using https://github.com/njvack/markdown-to-json to convert to JSON to make embedding to Eliza knowledge easier

## Customization

You can modify the script's behavior by adjusting:

- Model settings in `__init__`:
  ```python
  self.model = ChatOllama(
      model=model_name,
      temperature=0.2,
      num_ctx=4096,
      ...
  )
  ```
- Chunk size in `_chunk_messages`
- Analysis structure in `format_structured_prompt`
- Output formatting in `_format_markdown`

## Error Handling

The script includes:
- Graceful CTRL+C handling
- LLM initialization error catching
- Progress tracking
- Chunk processing error recovery


## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## Acknowledgments

- Uses [Ollama](https://ollama.ai/) for local LLM processing
- Built with [LangChain](https://python.langchain.com/) and [Rich](https://rich.readthedocs.io/)

## To-do

- Explore structured outputs from ollama
- Integrate into the Eliza framework
