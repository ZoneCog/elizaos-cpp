# 💻-coders 2024-11-18

## Summary
{The Discord chat segment focused on integrating solana token swaps into agents, with Ophiuchus providing a solution for waiting between replies using the setTimeout function in JavaScript code snippets. The community discussed rate limits and potential safeguards against them to prevent account suspensions or bans due to excessive interactions.}

## FAQ
- Has anyone successfully integrated solana token swaps into their agent? (asked by [0xwarptic](https://discordapp.com/users/@me/984231576))
- What solution did you use for waiting between replies on x? (asked by [Ophiuchus](https://discordapp.com/users/@me/984231576))
- Are the rate limits published right? (asked by [ferric | stakeware.xyz](https://discordapp.com/users/@me/984231576))
- Should we know if agents are talking to humans or not? (asked by [Oguz Serdar](https://discordapp.com/users/@me/984231576))
- If I want a blue checkmark on Twitter, should I use openvpn for routing traffic through the server's IP? (asked by [coinwitch (ai16z intern)](https://discordapp.com/users/@me/984231576))
- Can I leave TWITTER_COOKIES blank in the env file? If so, how does it get that on first run? What's best practice for handling this scenario? How to fix issues with Python installation and dependencies like ailon causing errors when running komorebi bot? Is there an alternative method such as using `pnpm` or Dockerfile instead of npm install command which seems not working properly, especially while trying to use the trump character feature in our project? (asked by @coinwitch (ai16z intern))
- Is there a 16z eliza youtube or twitch channel? (asked by @Teejay)
- How can the bot be programmed to only respond when directly mentioned? (asked by @Ophiuchus)
- How to create an official Eliza voice using elevenlabs Voice Design? Why did it fail due to looping issues? (asked by Oguz Serdar)
- What is the process for uploading chunks from a file in Git, similar to copy-pasting selected parts of code and pushing them upstream? (asked by @0xwarptic)

## Who Helped Who
- [Ophiuchus](https://discordapp.com/users/@me/984231576) helped Solana token swap integration issue by [0xwarptic] (solved successfully)  with Technical by providing Ophiuchus provided solution to wait between replies using setTimeout function
- [Oguz Serdar](https://discordapp.com/users/@me/984231576) helped Rate limit concerns by [ferric | stakeware.xyz] (solved successfully)  with Technical by providing Oguz Serdar suggested safeguards against rate limits
- @Binye helped @Zo with Resolved Python installation issues by installing necessary packages with `sudo apt install -y python3 python3-pip build-essential`. by providing @Ophiuchus provided guidance on handling Twitter API and bot registration. They also suggested using a mobile account for premium sign-up.
- @Thebishop helped @Dorian with Suggested using `pnpm run` command or Dockerfile for running the bot without encountering errors. by providing @Ophiuchus proposed a solution to prevent Discord rate limit burnout caused by other bots. The idea is embedding messages and tracking spamming users.
- @ferric | stakeware.xyz helped Community members struggling with ignored users in recentMessages. with Technical Tasks by providing Implemented context retrieval on messages
- @0xwarptic helped omzō with git operation by providing Ophiuchus provided guidance on using git commands to selectively push changes.
- @Ophiuchus helped @ashxn with Implementing phase-based twitter post/interaction system and setting conservative repo defaults to avoid spammy behavior. This was suggested by @ashxn as a solution for the Twitter agent's interaction frequency. by providing @Ophiuchus provided a cool down time set using temperature, which can be used to control the frequency of posts. This helped @ashxn with their issue regarding Twitter interactions.
- @Dorian helped General with  by providing @Dorian shared their work on video generation plugin, which could be useful in solving similar issues.
- @jamesID helped @collect with Adding Discord Client by providing @ashxn provided guidance on adding a discord client
- @collect helped Dockerfile setup issues and troubleshooting. with Technical Support - Docker Configuration Assistance by providing @BigSky

## Action Items

### Technical Tasks
- Integrate solana token swaps into agent (mentioned by [0xwarptic](https://discordapp.com/users/@me/984231576))
- Add solana plugin actions for send transactions (mentioned by [Ophiuchus](https://discordapp.com/users/@me/984231576))
- Implement safeguards against rate limits (mentioned by [Oguz Serdar](https://discordapp.com/users/@me/984231576))
- Deploy new twitter client with vision ai solution to replace current one (mentioned by [Oguz Serdar](https://discordapp.com/users/@me/984231576))
- Develop a solution to prevent other bots from burning Discord's rate limit by embedding messages and tracking spamming users. (mentioned by @Ophiuchus)
- Implement context retrieval on messages to remove ignored users from recentMessages (mentioned by @Ophiuchus)
- Create an environment for agents to respond only when directly mentioned (mentioned by @Ophiuchus)
- Prevent rate limiting on startup with OpenAI API (mentioned by moonboi)
- Determine a good default cooldown time for Discord (mentioned by @Ophiuchus)
- Investigate issues with Dockerfile causing problems for BigSky (mentioned by @BigSky)
- Investigate error handling for undefined 'text' property (mentioned by [supergordon](05:02))
- Set up a repo on Railway (mentioned by LiveTheLifeTV (05:33))

### Documentation Needs
- Publish best practices document with guidelines on using Twitter API, bot registration, premium account sign-up through mobile app. (mentioned by @Ophiuchus)
- Develop a 'dev-beginners' channel on Discord (mentioned by @ferric | stakeware.xyz)
- Explore hosting options and recommendations, including VPN/VPS services. (mentioned by [Lawyered.eth](04:56))

### Feature Requests
- Consider user verification for agent or human interaction (mentioned by [Ophiuchus](https://discordapp.com/users/@me/984231576))
- .env setting for bot response only when directly mentioned, with rate limits in place. (mentioned by @ferric | stakeware.xyz)
- Add Twitter client to character file and fill in .env details for the agent. (mentioned by ashxn)
- Work on agent dashboards/admin UI. (mentioned by @ashxn)
- Enable spontaneous communication between two Discord bots without @mentions, as requested by jamesID. (mentioned by @jamesID)