# 💻-coders 2024-11-08

## Summary
The conversation focused on implementing a tweet generation feature with random intervals between 4-8 hours. SotoAlt | WAWE provided guidance and code snippets for the implementation, while technoir suggested changing to an once per day frequency instead of every save action in order to avoid potential Twitter account restrictions.

## FAQ
- How can I make the agent that trades in Eliza codebase? What is Twitter config for frequency, relevancy etc. ? Who's replying to tweets and how long does it take to reply on twitter? (asked by ray (01:24))
- How can I change the interval of generateNewTweetLoop? What is searchAndEngage feature in Eliza codebase ? (asked by technoir (02:35))
- Where do I go to set up an agent? What does it mean in this ecosystem and what resources are available for setting one up? (asked by @slim)
- where is Shaw's daily stream located (asked by @SotoAlt | WAWE)
- Is there any value in keeping track of who developed which Agent? and the answer by @whobody (asked by @flockaflame)
- What's next after setting up an AI agent for a Solana-Telegram crypto gaming project, specifically managing accounts/wallets & answering questions from docs? (asked by @lucyfer)
- Why is new knowledge not having as much effect on the SQLite database? What could be causing this issue? (asked by @hiroP)
- What's the difference between https://github.com/raphaelmansuy/code2prompt and https://github.com/mufeedvh/code2prompt APIs for creating dashboards? (asked by @jin)
- Can I setup a 2 sol bounty on how to video? Would benefit everyone! :) (End-to-end Twitter, Discord, Telegram?) Caveats included please. Explain like in five haha. (asked by [Bless](21:37))
- Has anyone documented setting up an Eliza twitter bot from start to finish? (On video lol) (asked by [Bless](20:18))

## Who Helped Who
- technoir (02:35) helped ray(01:24) with Find relevant information in generateTweet function. by providing SotoAlt | WAWE provided guidance on how to find and use Twitter config for frequency, relevancy etc. They also suggested asking the cursor about these details.
- technoir (02:35) helped ray(01:24) with Implement once per day interval in generateNewTweetLoop. by providing SotoAlt | WAWE provided code snippet for the onReady() method and explained how to change tweet generation frequency.
- @technoir helped @LiveTheLifeTV with Resolving technical issues by providing @LiveTheLifeTV was stuck and @technoir provided a solution to rebuild with node v23, which resolved the issue.
- @hiroP helped  with Agent setup guidance by providing @hiroP shared their experience of setting up an agent and offered feedback on it.
- @flockaflame helped  with  by providing 'LLM runs locally' clarification by @hiroP
- @lucyfer helped @hiroP with Suggested starting point for AI agent development by providing @whobody
- @jin helped Need help with making a dashboard uv map. Slim provided guidance on potential loading or network issues. with Troubleshooting Dashboard UV Map Creation by providing @slim
- [Ophiuchus](21:11) helped [Bless] with Setting up an eliza twitter bot from start to finish by providing Ophiuchus offered documentation for the latest build of Eliza, including adding tweeting cookies.

## Action Items

### Technical Tasks
- Implement tweet generation feature with random interval between 4-8 hours (mentioned by SotoAlt | WAWE)
- Rebuild with node v23 (mentioned by @LiveTheLifeTV)
- Implement local LLMs for chatbots (mentioned by @whobody)
- Investigate SQLite vector extensions for token swaps (mentioned by @Ophiuchus)
- Document process for setting up Eliza Twitter bot on latest build, including adding tweeting cookies. (mentioned by [Ophiuchus](21:11))
- Create a comprehensive video tutorial covering Eliza setup from start to end, including Twitter and other platforms. (mentioned by [Ophiuchus](23:04))

### Documentation Needs
- Change the frequency of generateNewTweetLoop to once per day for now. (mentioned by technoir)
- Standard wording for agents, similar to horse descriptions. (mentioned by @hiroP)
- Explore Helius and Birdeye APIs to understand their functionalities. (mentioned by @Ophiuchus)

### Feature Requests
- Enable image generation with text input (mentioned by @Gozde)