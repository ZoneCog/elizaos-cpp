import json
from datetime import datetime
from pathlib import Path
from collections import defaultdict
import argparse

def parse_timestamp(timestamp_str):
    """Parse timestamp with variable precision in fractional seconds."""
    try:
        # First try standard ISO format
        return datetime.fromisoformat(timestamp_str.replace('Z', '+00:00'))
    except ValueError:
        try:
            # Handle variable precision in fractional seconds
            date_part, tz_part = timestamp_str.rsplit('-', 1)
            # Ensure consistent precision for fractional seconds
            if '.' in date_part:
                base, frac = date_part.rsplit('.', 1)
                # Pad to 6 digits (microseconds)
                frac = frac.ljust(6, '0')
                date_part = f"{base}.{frac}"
            # Reassemble with timezone
            normalized_timestamp = f"{date_part}-{tz_part}"
            return datetime.fromisoformat(normalized_timestamp)
        except Exception as e:
            print(f"Error parsing timestamp '{timestamp_str}': {e}")
            raise

def clean_message(message, user_map):
    """Create minimal message format, omitting null/empty fields."""
    user_id = message['author']['id']
    
    # Add user to map if not exists, only including non-empty fields
    if user_id not in user_map:
        user_data = {}
        if name := message['author'].get('name'):
            user_data['name'] = name
        if nickname := message['author'].get('nickname'):
            user_data['nickname'] = nickname
        if roles := [r['name'] for r in message['author'].get('roles', []) if r.get('name')]:
            user_data['roles'] = roles
        if message['author'].get('isBot'):
            user_data['isBot'] = True
            
        user_map[user_id] = user_data
    
    # Build message dict only with non-null values
    msg = {
        'id': message['id'],
        'ts': message['timestamp'],
        'uid': user_id,
        'content': message['content']
    }
    
    # Only add optional fields if they have values
    if message_type := message.get('type'):
        if message_type != 'Default':  # Don't include if it's Default
            msg['type'] = message_type
            
    if edited := message.get('timestampEdited'):
        msg['edited'] = edited
        
    if mentions := [m['id'] for m in message.get('mentions', []) if m.get('id')]:
        msg['mentions'] = mentions
        
    if ref := message.get('reference', {}).get('messageId'):
        msg['ref'] = ref
        
    if reactions := message.get('reactions'):
        cleaned_reactions = [{'emoji': r['emoji'].get('name'), 'count': r['count']} 
                           for r in reactions]
        if cleaned_reactions:
            msg['reactions'] = cleaned_reactions
            
    return msg

def simplify_chat_export(input_file, output_dir='simplified_chats'):
    """Process Discord chat export into simplified daily files with user mapping."""
    # Load the input file
    with open(input_file, 'r', encoding='utf-8') as f:
        data = json.load(f)
    
    # Extract channel info and ID
    channel_info = {'id': data['channel']['id']}
    if name := data['channel'].get('name'):
        channel_info['name'] = name
    if topic := data['channel'].get('topic'):
        channel_info['topic'] = topic
    if category := data['channel'].get('category'):
        channel_info['category'] = category
    
    channel_id = channel_info['id']
    
    # Create a subdirectory based on the channel ID
    channel_output_path = Path(output_dir) / str(channel_id)
    channel_output_path.mkdir(parents=True, exist_ok=True)
    
    user_map = {}
    daily_messages = defaultdict(list)
    
    for message in data.get('messages', []):
        ts = parse_timestamp(message['timestamp'])
        day = ts.strftime('%Y-%m-%d')
        
        cleaned_msg = clean_message(message, user_map)
        if cleaned_msg['content']:  # Only keep messages with content
            daily_messages[day].append(cleaned_msg)
    
    # Write daily files
    for day, messages in daily_messages.items():
        output_file = channel_output_path / f'chat_{day}.json'
        
        output_data = {
            'channel': channel_info,
            'date': day,
            'users': user_map,
            'messages': messages
        }
        
        with open(output_file, 'w', encoding='utf-8') as f:
            json.dump(output_data, f, indent=2, ensure_ascii=False)
            
    return len(daily_messages)


def main():
    parser = argparse.ArgumentParser(description='Simplify Discord chat export')
    parser.add_argument('input_file', help='Input JSON file path')
    parser.add_argument('output_dir', help='Output directory for simplified files')
    
    args = parser.parse_args()
    
    num_files = simplify_chat_export(args.input_file, args.output_dir)
    print(f'Successfully created {num_files} simplified daily files')

if __name__ == '__main__':
    main()
