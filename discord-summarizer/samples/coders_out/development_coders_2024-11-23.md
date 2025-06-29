# 💻-coders 2024-11-23

## Summary
The main technical discussion revolved around an error from the postgres database adapter method `searchMemories`. A solution was proposed by @ICJR to add `.catch(() => ({ rows: [] }))` in order to stop errors. Additionally, there were discussions about a bio link swap incident involving @timshel.

## FAQ
- Was there a pr with quote rt and likes? Can't find it now.','answered_by': null}],   ,    { (asked by @SotoAlt | WAWE)
- Is the bio link swap intentional or an accident caused by postgres package? Is there any way to prevent this in future?, (asked by @Bloom1)
- What's your opinion on @timshel changing his bio and denying it later? (asked by @solarnius)
- How do you train an agent with tweets from other people? How can I feed it every tweet from a Twitter account without scraping the entire timeline and putting them in character files? (asked by [18 Rabbit (00:49)])
- Is there any way to rate limit usage of the Twitter API when using a scraper? I accidentally DDOS'd myself. (asked by [void(null) ⍼ (01:28)])
- Does anyone know what's the path to get into this bit of code that's showing error? What is causing it and how can I fix it? How do you run pnpm i, build, start commands correctly without errors? (asked by @Teo)
- What’s proper formatting for adding plugins to character JSON data structure in the project files like index.ts or elsewhere?” }],   // FAQ questions and answers are not provided as they were missing from your input text, please provide them if you want me include it here  },    {      (asked by @björn)
- Can we check for any additional logs that might help diagnose the problem? What is causing pnpm i to fail and how can I resolve this issue? (asked by @Galego)
- 'I installed eliza-starter and working fine on command line but i cant get it to talk to my bot on discord - I have setup the token, application id, added discord token in .env file. What am I missing?'',  # Discord integration issue with Eliza Starter (asked by [Gr0in])
- 'I get error 'Command build' not found for pnpm and !./agent event not found. How can I resolve this?' (asked by [Teo (02:38)])

## Who Helped Who
- @ICJR helped @Ophiuchus with Error investigation by providing Suggested adding `.catch(() => ({ rows: [] }))` to stop errors from the postgres database adapter method `searchMemories`.
- @solarnius helped All with Community support by providing Shared personal experience with @timshel's bio link swap incident.
- [void(null) ⍼] helped [Twitter API usage and rate limiting] with Provided information on using Twitter scraper, but advised to check for the need of a Twitter API. by providing [SotoAlt | WAWE (01:28)]
- [björn (01:41) and others] helped [Setting up agents to communicate locally] with Shared a GitHub repository link for scraping tweets into character files. by providing [Galego (01:36)]
- @Galego helped @Teo with Resolving pnpm i installation error. by providing Guided Teo through troubleshooting steps, including checking project folder structure.
- [Galego] helped [Teo] with Discord Bot Integration by providing [Gr0in's bot integration issue with Eliza Starter, Galego provided guidance for running pnpm build within wsl environment.
- Ophiuchus helped copycat with Resolving Module not found errors by providing Teo suggested trying wsl on Windows systems and running Eliza without adding keys or making changes.
- Galego helped  with Resolving an issue with running `eliza` by providing Galego provided steps to fix the 'EADDRINUSE' error
- [Ophiuchus](at 2021-09-27T03:41) helped [Msurfx] with Resolve port conflict issue with Eliza bot (successful help interaction) (at 2021-09-27T05:46) by providing [not in a dao ai] explains port conflict and how to resolve it (at 2021-09-27T04:58)
- [Spicy (Repenting for my Sins)](at 2021-09-27T04:36) helped [Msurfx] with Update Eliza to version v0.1.4-alpha.3 and fix code issue (successful help interaction) (at 2021-09-27T05:46) by providing [Galego] suggests updating to version v0.1.4-alpha.3 and removing 'typeof DirectClient' from code(at 2021-09-27T05:08)

## Action Items

### Technical Tasks
- Investigate error from postgres database adapter method `searchMemories` (mentioned by @Ophiuchus)
- Train an agent with tweets from other people (mentioned by [18 Rabbit (00:45)])
- Implement agents to communicate locally and rate limit Twitter API usage (mentioned by [björn (01:39), void(null) ⍼ (01:28)])
- Investigate error during pnpm i installation (mentioned by @Teo)
- Run pnpm install again (mentioned by [Teo (02:23)])
- Execute 'pnpm build' command for Windows users within WSL environment. (mentioned by [Galego (02:35, 02:41)])
- Install pnpm again inside the wsl for Teo's issue. (mentioned by [Galego (02:36)])
- Check if wsl is active on Windows systems (mentioned by Ophiuchus)
- Resolve 'EADDRINUSE' error when running `pnpm start` (mentioned by Msurfx)
- Resolve port 3000 conflict by identifying & terminating conflicting process (mentioned by [not in a dao ai] (at 2021-09-27T04:58))
- Update Eliza to version v0.1.4-alpha.3 (mentioned by [Galego] (at 2021-09-27T05:08))
- Change SERVER_PORT to a different value (mentioned by [0xM1M3 (04:25)])

### Documentation Needs
- Setup Discord bot using DISCORD_APPLICATION_ID in character.json (mentioned by [void(null) ⍼ (01:02)])
- Review plugin formatting in character.ts file for proper integration with JSON data structure. (mentioned by @björn)
- Update .env file with new SERVER_PORT and OpenAI key (mentioned by [guru (03:48)])

### Feature Requests
- Add `.catch(() => ({ rows: [] }))` to stop errors in the same context. (mentioned by @ICJR)
- Add max turns feature to the character file (mentioned by [void(null) ⍼ (01:28)])
- Use a stable build instead of an alpha version for Eliza installation (mentioned by RL)
- Configure tweet frequency with Eliza starter (mentioned by [Ray Zhu] (at 2021-09-27T05:43))
- Define rules in twitterShouldRespondTemplate for bot to respond based on user's tweets or topics (mentioned by [Ray Zhu (04:25)])