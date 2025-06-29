# 💻-coders 2024-10-31

## Summary
The chat focused on implementing stock market screens using TradingView widgets, resolving npm run errors by setting intents in the Discord developer page and clarifying misunderstandings about connecting an X account. The community members provided helpful solutions to these technical challenges.

## FAQ
- What to do when encounter 'Error: Used disallowed intents' in npm run? What are the steps for setup? (asked by @istyping)
- Is a subscribed account required (blue) to connect an X account that returns error code 399 with message 'Sorry, we could not find your account.' (asked by @Ofir)
- Should I pay OpenAI to fix the API error? (Error: Error: OpenAI API Error: 429 Too Many Requests or there is workaround to run in local since it's just experiment) (asked by [istyping](01:54))
- Great! It works. Thanks! (asked by [istyping](03:14))
- Did you use the default character? Then check secret obj and TWITTER_USERNAME to ensure it is your account. (asked by @istyping)
- Can u debug with cursor and see what it says? (asked by @SotoAlt | WAWE)
- Still facing different issue after login. Any suggestions? (asked by @istyping)
- Any updates on the Twitter account login problem in this thread? (asked by patabrava.eth)
- Any idea of a repo that I can use to test the functionality of an agent controlling wallet completely? (asked by [patabrava.eth](07:15))
- Do I need eleven labs account for Eliza? (asked by [Agent Joshua $ (09:43)])

## Who Helped Who
- @Lazarou helped @istyping with Resolving 'Error: Used disallowed intents' by providing @Lazarou provided solution for '@istyping's npm run issue by suggesting setting intents on the Discord developer page.
- @big_d ookie helped @ofir with Understanding X account connection issues. by providing @big dookie clarified that '@Ofir's issue was due to a misunderstanding of the error message.
- [SotoAlt | WAWE](02:03) helped [istyping](01:54) with Resolving OpenAI API Error by providing SotoAlt | WAWE provided solution to resolve OpenAI API Error by restarting the bot and creating a new api key
- @istyping helped Jb (06:21) with Fix defaultCharacter.ts file by providing Resolved characterPath undefined by replacing 'eliza__v1' with actual username
- @SotoAlt | WAWE helped istyping (06:54) with Resolve Twitter account login by providing Suggested deleting db.sqlite and restarting the app after creating a new API for user ID retrieval issue.
- [SotoAlt | WAWE] (07:19-07:20) helped [patabrava.eth](07:15) with Test agent controlling wallet functionality by providing Adding server URL in .env file
- [big dookie (07:45)] helped [chat_group] with Enable agents to post on Twitter automatically by providing Providing GitHub repo for Twitter posting feature
- @Ophiuchus helped @Tenji with Technical Assistance by providing Guided Tenji to rename and back up local LLAMA-3.1 model for proper usage.
- @Ophiuchus helped All members with Finding resources on different models by providing Ophiuchus provided a link to an AI leaderboard for model comparisons.
- [LevelsDennis](14:38) helped [Ophiuchus] with Setting up Colab Environment by providing Ophiuchus provided a script shared by LevelsDennis on how to install colab dependencies and setup environment.

## Action Items

### Technical Tasks
- Implement stock market screens using TradingView widgets (mentioned by @jin)
- Restart bot to resolve OpenAI API Error: 429 (mentioned by [SotoAlt | WAWE](02:03))
- Create a new api key for OpenAI after restarting the bot and ensuring correct setup (mentioned by [SotoAlt | WAWE](02:04))
- Resolve Twitter account login issue by checking .env file for correct TWITTER_USERNAME (mentioned by @SotoAlt | WAWE)
- Delete db.sqlite and restart the application after creating a new API with $5+ credits for resolving user ID retrieval issue (mentioned by @SotoAlt | WAWE)
- Add server URL to .env for agent controlling wallet functionality (mentioned by [SotoAlt | WAWE](07:19))
- Rename model file to 'model' & place it within services folder, ensuring a backup is made. (mentioned by Ophiuchus)
- Explore memory setup for AI models (mentioned by @Ophiuchus)
- Explore switching models at endpoint using red-pill.ai & AgentWars (mentioned by [Ophiuchus](14:13))
- Check out modified llama.ts that uses ollama instead, not productional due to lack of endpoint/embedding model customization (mentioned by [Ophiuchus](14:17))
- Rebuild character generator using local models, rate out top characters for creating files. Example provided with Eliza's Sister (mentioned by [Ophiuchus](14:19))
- Install llama using npx --no node-llama-cpp download (mentioned by @Ophiuchus)

### Documentation Needs
- Set up intents on the Discord developer page for npm run error resolution. (mentioned by @Lazarou)
- Replace 'eliza__v1' with actual Twitter username in defaultCharacter.ts file to resolve characterPath undefined issue (mentioned by @istyping)
- Remove OpenAI API key for local usage of the agent (mentioned by big dookie and Ophiuchus)
- Report findings on different model comparisons and strengths vs weaknesses. (mentioned by @Bushi)
- Install colab dependencies and setup environment using the script shared by Ophiuchus for eliza project. (mentioned by [LevelsDennis](14:38))

### Feature Requests
- Implement better timestamp retrieval to identify speaker in input audio, considering words per second spoken (mentioned by [big dookie](02:05))
- Consider adding Twitter posting feature in main repo. (mentioned by [big dookie (08:56)])
- Test openai with the provided code snippet from Agent Joshua ₱. (mentioned by @AgentJoshua)