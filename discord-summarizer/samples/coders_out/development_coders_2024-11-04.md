# 💻-coders 2024-11-04

## Summary
The discussion focused on optimizing a file for language-based metrics instead of wallet spending behavior. DorianD faced issues running the project without an Nvidia card, and received advice to ensure AI framework compatibility with alternatives or use cloud GPU providers.

## FAQ
- What is boredom.ts? Is it a gross attempt at something specific? (asked by shaw)
- I'm David, can I discuss open positions or projects with you guys? (asked by Wahaha0528)
- How can we adapt to the tools at our disposal in a fast-paced environment? What configurations unlock significant potential? (asked by @pmairca)
- What is causing an error with Twitter cookies, and how do I resolve it using Get Cookies.txt locally or agent-twitter-client approach? (asked by @DorianD)
- What's a good model for image gen? Stuff like truth terminal is generating now. Gonna work on this today. (asked by @Tenji (05:09))
- Need it to do what? (asked by @whobody (06:10))
- Can I give it prompt using voice? How to do that? (asked by @Jb)
- Is there any docs for character creation (asked by @j2k)
- Where can we find documentation and updates on the project (asked by @Hackor, @jin)
- How to create an uwuposter for unicorn with limited available data? (08:51) (asked by @j2k)

## Who Helped Who
- pmairca helped DorianD with Troubleshooting GPU issues by providing DorianD received help on AI framework compatibility for non Nvidia cards
- Airmax helped @pmairca @shaw with Resource sharing by providing Strawberry.ai resources recommended by Airmax to pmairca and shaw, including sentiment analysis bot
- @pmairca helped @DorianD with Resolved by providing Troubleshooting ModelProvider configuration for twitter API.
- @ferric | stakeware.xyz helped @DorianD with Resolved by providing Provided solution to Twitter cookies error using agent-twitter-client approach or Get Cookies.txt locally and copying JSON into .env file.
- @lina-bytes helped @Tenji with image gen model selection by providing @Tenji was given advice by @lina-bytes on image generation models and potential use of Stable Diffusion Flux for better results.
- @stakeware.xyz helped @Jb with Voice prompt setup by providing @ferric provided instructions to debug voice input using Discord's TTS feature.
- @jin helped @AzFlin;@standard with Documentation sharing by providing @jin shared documentation links and requested feedback on docs, @Hackor pointed out a GitHub repo for character files.
- @kellyn helped @jin, @smokyboo with Tracking and organizing information on future events. by providing @kellykellz suggested creating a shared spreadsheet to track upcoming AI hackathons/contests.
- @agent_joshua helped @kellyn, @jin with Providing support for upcoming event participation. by providing @Agent Joshua offered help to devs interested in the 'Best Use of AI' track at ETHGlobal Nov. 15-17 bounty.
- @AzFlin & @maxim.sui🌊 helped Eliza installation issue with Shared solution for package.json modification to get Eliza working locally by providing @Lazarou

## Action Items

### Technical Tasks
- Translate file purpose from tracking wallet spending to language-based metric (mentioned by ATH🥭Hivo)
- Implement ModelProvider configuration for Twitter API (mentioned by @pmairca)
- Explore Stable Diffusion Flux for image generation (mentioned by [Tenji, Nona (ag/acc)])
- Install dependencies using pnpm, including optional sharp package (mentioned by @AzFlin)
- Get a list of upcoming AI hackathons/contests and create shared spreadsheet for tracking. (mentioned by @jin, @kellykellz)
- Run 'npm install eliza' after running pnpm commands (mentioned by yung_algorithm)
- Implement image uploading functionality for `sendTweet` (mentioned by [AzFlin](16:44))
- Investigate the possibility of using GraphQL with Twitter API for image uploading and tweeting (mentioned by [AzFlin](16:47))
- Update `agent-twitter-client` to support GraphQL with Twitter API if possible, or improve current workaround (mentioned by [AzFlin](16:48))
- Building warpcast client (mentioned by @Bushi)

### Documentation Needs
- Ensure AI framework compatibility for non Nvidia cards, consider cloud GPU providers (mentioned by DorianD)
- Resolve issue with twitter cookies in Eliza project using agent-twitter-client or similar approach. (mentioned by @ferric | stakeware.xyz)
- Develop a consistent art style dataset tutorial (mentioned by [whobody])
- Create documentation for installation errors + fixes (mentioned by AzFlin)
- Update the installation section of docs to reflect changes in package manager (pnpm) (mentioned by DorianD)
- Resolve unecessary redundancy in documentation (quickstart, installation and basic usage) (mentioned by [jin])

### Feature Requests
- Update better-sqlite3 to a version compatible with Node.js v13+. (mentioned by @cc @jin)
- Create an uwuposter for unicorn with limited available data (mentioned by @j2k)
- Cleanup/improvement of the installation process (mentioned by AzFlin)
- Add warning for default configs causing bot flagging on Twitter (mentioned by [SotoAlt | WAWE])