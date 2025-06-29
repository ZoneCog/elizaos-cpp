# 💻-coders 2024-11-10

## Summary
The chat focused on technical discussions about running the 'LLAMALOCAL' environment, where Deniz encountered an issue linking hermes-3-lIama file to runtime. Nirai Kanai asked if vision capabilities could be switched in claude models and Arthuryeti sought help with scraping large collections using LM Studio without hitting rate limits.

## FAQ
- Is it possible to switch vision capabilities of claude? It seems like the vision capability is tied to openai, but I find claude version much better. Seems like when you change the model, the vision stops working. (asked by @nirai kanai)
- I'm getting `Authentication attempt 1 failed: { (asked by @arthuryeti)
- Has anyone been able to successfully call the 'swap' function? I have registered it but no tokens are being exchanged. Here is a screenshot of my issue: https://i.imgur.com/5X4JnL1.png (asked by @ray)
- Can we chat with our agent in the terminal or anywhere other than Twitter? I don't want to set up any accounts for now, just checking if it can communicate. (asked by @ray)
- Where can I find the .env.example file? How do I use it to set up environment variables for Supabase and OpenAI API keys? What are the correct paths, contents of files needed in root folder with specific data included? (07:47 - 12:16) (asked by @whobody)
- What commands should I run after copying .env.example file to set up the environment for Eliza project using pnpm and npx with GPU support? (08:34 - 12:06) (asked by @exHuman)
- What was your workaround for the issue?
Answer: Swapped over to PostgreSQL and set up `POSTGRES_URL` in .env file. 
Responder: @Ophiuchus (asked by @standard)
- Is there a solution for SQL? (15:59) - Yes, the provided code snippet demonstrates how to handle queries with JSON input and embeddings stored as BLOBs in PostgreSQL. The function 'getCachedEmbeddings' is used for this purpose. (asked by @Ophiuchus)
- Is postgres working? (15:49) - Yes, Eliza confirmed that the issue with node-pre-gyp installation was unrelated to PostgreSQL. The database seems functional as per her statement at 18:27. (asked by @Eliza)
- Is there a time limit for posting? How long does it take to generate new tweets? Can you set the interval between posts? (asked by @Ophiuchus (19:47))

## Who Helped Who
- @arthuryeti helped  with Scrape a collection of tweets without hitting rate limits by providing @not_in_a_dao_ai provided settings for scraping large collections with local models in LM Studio.
- @not_in_a_dao_ai helped @arthuryeti with Resolving connection issues with NordVPN by providing Suggested Mullvad VPN as a secure alternative to NordVPN.
- @Rick (shared) helped @hiroP with Reinforcing the recommendation for using Mullvad by providing Shared tweet about Mullvad VPN by @whobody.
- @arthuryeti helped @exHuman with agent environment setup by providing @not_in_a_dao_ai provided a solution by suggesting cloning Eliza repo onto Mac
- [standard](7:47) helped @whobody with Guided user to find and use the .env.example file for setting up environment variables. by providing @exHuman
- [Rick](10:03) helped @exHuman with Provided encouragement and reassurance to continue working on the project. by providing @not_in_a_dao_ai
- @standard helped @Ophiuchus with Database setup and documentation writing. by providing @buchla helped with setting up a pg db for vector enabled tables
- @Eliza helped @LevelsDennis with Resolve node-pre-gyp installation issue by providing @Eliza provided guidance on resolving a technical problem related to the 'node-pre-gyp' installation, suggesting running `npm install --force-reinstall` as per LevelsDennis’ issue at 18:57.
- @Ophiuchus helped @Eliza with Provide information on accessing documents & codebase by providing Ophiuchus inquired about Eliza's access to the documentation and codebase at 19:47.
- @Eliza helped LevelsDennis (19:47) with Resolving technical issue with Twitter post activation. by providing @Eliza provided a solution for node-pre-gyp installation issues

## Action Items

### Technical Tasks
- Link hermes-3-lIama file to runtime for LLAMALOCAL (mentioned by @Deniz)
- Install Mullvad VPN for secure browsing without logs (mentioned by @not_in_a_dao_ai)
- Clone Eliza repo onto Mac for agent environment setup (mentioned by @not_in_a_dao_ai)
- Set up environment variables for Supabase, OpenAI API (mentioned by [exHuman](09:11))
- Switch to PostgreSQL for better performance (mentioned by [standard, buchla])
- Resolve node-pre-gyp installation issue (mentioned by @LevelsDennis)
- Run `npm install --force-reinstall` to resolve node-pre-gyp installation issue (mentioned by @Eliza)
- Resolve node-pre-gyp install issue by running `npm install --force-reinstall` (mentioned by @Eliza)
- Investigate node-pre-gyp installation issue (mentioned by @Eliza)
- Troubleshoot Twitter persona issue with nirai kanai (mentioned by [nirai kanai](21:24), Eliza (multiple times))

### Documentation Needs
- Add delay between requests when scraping large collections with local model in LM Studio. (mentioned by @arthuryeti)
- Set up environment variables and run npm script to interact with Twitter API (mentioned by @not_in_a_dao_ai)
- Install dependencies using pnpm and npx commands. (mentioned by [exHuman](8:34))
- Update .env file with `POSTGRES_URL` pointing to new database. (mentioned by [Ophiuchus])
- Update documentation for changes since v0.0.5, specifically Twitter post activation issues. (mentioned by 0x𝒲𝒶𝓁𝒸𝒽 ⚡🦇)
- Read logs to identify context or state fumbling issues. (mentioned by standard(21:25))

### Feature Requests
- Call swap function as an action in the agent environment and verify token swapping. (mentioned by ray)
- Create video demonstrating new build and features on Discord Marketplace & Bounties platform. (mentioned by @Ophiuchus)
- Investigate and fix looping glitches in the arena. (mentioned by @Ophiuchus)
- Explore potential solutions for repetitive patterns in outputs and Twitter persona limitations. (mentioned by @nirai kanai)