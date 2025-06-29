# 💻-coders 2024-11-20

## Summary
The chat segment focused primarily on the technical aspects of Eliza's development and deployment. YoungPhlo successfully ran an instance, aiming to tweet with two model providers by a specific date (1/20). Issues were discussed regarding version control using git checkout v0.0.10 due to missing character files in newer versions.

## FAQ
- Why does pnpm build fail after a successful install? Who can help with this issue? (asked by @18 Rabbit)
- How to provide the openAI API key for Eliza using Ollama starter without getting an error message? (asked by @LanaDelFade)
- Why does eliza make rapid posts to its own tweets? What's the issue with openai and grok api settings in .env file? (asked by @Kanye)
- What is causing errors when generating new Tweets using Twitter client after pulling a recent update, specifically related to tokenizer.json not found at /Users/0xvitae/dev/darksun/packages/core/cache/fast-bge-small-en-v1.5/? (asked by @björn)
- How to create realistic selfies using image model? Any suggestions for a Twitter thotposter plugin? (asked by liamz)
- What branch are you on if the new agent folder isn't working? (asked by dnx)
- How do I launch an Agent? Can you explain this process to me as I'm stuck. The answer was provided by Odilitime. (asked by Kanye)
- Is it wise for multiple people working on the same concept, or is more beneficial if someone has already done it? (asked by UoS)
- Why can't I generate a new tweet? What should be done to fix this issue? (asked by @björn (02:41))
- What provider is being used for the current implementation, as suggested by LanaDelFade in her solution? (asked by @loaf (02:43))

## Who Helped Who
- @DorianD helped @Mili with Provided information on root access requirements for using Python in Replits. by providing Mili asked about running Eliza online, similar to replit.
- @LanaDelFade helped @UoS with Resolving a build failure after successful npm install by providing 18 Rabbit provided help on pnpm installation issue.
- @Kanye helped All users facing similar issues with Resolving errors related to OpenAPI keys in .env file by providing @SatoshiWolf provided guidance on fixing openapi key error and ensuring correct environment setup for Grok API.
- dnx helped LiamZ with Creation of a Twitter thotposter using an image model by providing liamz received advice from dnx to write his own selfie-creating AI plugin or use PhotoAI service.
- dnx, loaf helped LanaDelFade with Resolving AI API call errors by providing LanaDelFade received help from others to change model provider and resolve an error. The issue was resolved by ensuring Ollama output in JSON format.
- @LanaDelFade (02:43) helped @björr with Editing character.ts file in src instead of using OPENAI. by providing Lana Del Fade provided a workaround to björn's issue with generating new tweets.
- @RL helped @SotoAlt | WAWE with Debugging & Troubleshooting by providing Addressing character update issue after deleting DB SQLite and rebuilding
- @18 Rabbit helped Twitter tweeting setup and node-scheduler switch. with Provided guidance on setting up Twitter credentials in .env file. Suggested switching to Node Scheduler for better functionality by providing @rckprtr
- [infi](https://discordapp.com/users/@me) helped bot time awareness with Suggested using TimeProvider (04:23) by providing [RL](https://discordapp.com/users/@me)
- @RL helped [@Lawyered, @18 Rabbit] with Fixing bot's Twitter posting issue by providing RL provided tips for fixing rate limiter issues and updating software versions.

## Action Items

### Technical Tasks
- Investigate DNS or internet issues causing pnpm install error (mentioned by @18 Rabbit)
- Resolve pnpm install error (mentioned by 18 Rabbit)
- Comment out open API key variable by adding '#' before it (mentioned by @18Rabbit)
- Create a plugin for realistic selfies using image model (mentioned by liamz)
- Resolve AI API call error by ensuring Ollama output is JSON (mentioned by LanaDelFade)
- Resolve error generating new tweet due to missing tokenizer file (mentioned by björn)
- Connect Supabase properly for memory management (mentioned by @redbull.eth)
- Set up Twitter credentials (mentioned by @maz)
- Implement a TimeProvider for bot to know current time (mentioned by [RL](https://discordapp.com/users/@me))
- Investigate and fix the issue with Claude bot posting profound sounding stuff (mentioned by [bngus](https://discordapp.com/users/@me))
- Implement a rate limiter for bot activity (mentioned by @Lawyered)
- Implement rate limiting code snippet from dotenv file (mentioned by @RL)

### Documentation Needs
- Handle missing environment variables in eliza-starter project. (mentioned by UoS)
- Replace OPENAIKEY with actual Grok settings in .env file and ensure env is located within the core/ folder. (mentioned by @SatoshiWolf)
- Set up a new branch for working on the agent concept (mentioned by UoS)
- Edit character.ts in src instead of using OPENAI, as suggested by LanaDelFade. (mentioned by LanaDelFade)
- Switch to node-scheduler for tweeting functionality. (mentioned by @rckprtr)
- Update to the latest version of software (v0.1.3-12g8cb3467) (mentioned by bngus)

### Feature Requests
- Train own lora/model or use PhotoAI service and integrate it into the plugin. (mentioned by dnx)
- Explore Twitter dry run feature for bot integration (mentioned by [infi](https://discordapp.com/users/@me))