# 💻-coders 2024-11-16

## Summary
Discussion focused on resolving technical challenges, such as Docker and Node.js versioning errors; implementing new features like image uploads to tweets using agent-twitter-client; exploring the use of Replit in development workflows; addressing concerns about ONNX Runtime API initialization issues.

## FAQ
- Should I do full stack stuff if good at math? (00:42) (asked by sebasv23)
- How to change Node.js version from v23.2.0 to v23.1.0 ?(02:09) (asked by Iodine)
- Do I need to purge any files for the new persona based on ltl.json? (asked by @LiveTheLifeTV)
- How do I start bot from a clean slate after deleting db.sqlite? (asked by @walee)
- How can I wipe memory and start afresh? How do you delete the SQL database, didn't work for me. Thanks will try to re-fork. (asked by [walee])
- Delete db sql (asked by [SotoAlt | WAWE])
- How do I get Eliza's framework to work and launch my coin? (asked by [RonnySeibt])
- how are you guys hosting this? vps? (asked by [shrigma male (04:38)])
- What exactly is needed here and how does Eliza get embed in to the process of completing this particular bounty? (asked by [! ! ! Lewpik])
- Hey everyone, full stack JS dev here... What's a good starting point? Do I just clone the repo and try to get it to work with ChatGPT? (asked by [wojt175(06:28)])

## Who Helped Who
- LiveTheLifeTV (00:45) helped  with Troubleshooting docker issues for a X account. by providing Resolved Docker issue and got the project running again
- @SotoAlt|WAWE helped @LiveTheLifeTV with Comparing AI models for better performance. by providing SotoAlt | WAWE confirmed Claude's superiority over OpenAI API.
- [SotoAlt | WAWE (04:25-04:31)] helped [walee] with Troubleshooting and resolving issues with OpenAI. by providing [SotoAlt | WAWE] suggested using Claude over OpenAI, deleting SQL database if needed.
- [7OROY (05:21)] helped [@Roque] with Providing guidance on using Eliza's framework in conjunction with a Discord server. by providing [7OROY] suggested waiting for @jin to answer the question about interacting with Discord bot.
- @shrigma male helped @jin with Adding Context by providing @jin, help with adding context (06:23)
- @Roque helped @Noah with Connecting AI Model with Discord Bot by providing @Roque asked about connecting Llama model agent to Discord bot, @Noah acknowledged the issue but didn't provide a solution.
- [bacon](07:15) helped [KothCap](07:03) with Bot building assistance by providing [kbrownfitness](07:04) offered to help bacon later if their bot is up and running
- [bacon](07:15) helped [KothCap](07:03) with Troubleshooting bot building issues by providing [kbrownfitness](07:04) asked bacon where they are stuck to provide targeted help
- @AMcKay, @Nona (ag/acc) helped @kbrownfitness with Resolving technical issues by providing kbrownfitness received help from others to resolve rate limiting issue with Claude API
- [SotoAlt (WAWE) @07:42-@08:05] helped [Roque (@08:03)] with Troubleshooting Discord client initialization and interaction issues. by providing SotoAlt | WAWE provided guidance on initializing the Discord client and using defaultCharacter

## Action Items

### Technical Tasks
- Resolve onnxruntime-node VERS_1.19.2 error (mentioned by Neodotneo)
- Purge tweet cache folders for LiveTheLifeTV character update (mentioned by @LiveTheLifeTV)
- Empty db.sqlite to start bot on a clean slate as suggested by walee. (mentioned by @walee)
- Revert back to OpenAi for troubleshooting (mentioned by [walee (04:25)])
- Delete SQL database and re-fork code if necessary. (mentioned by [SotoAlt | WAWE (04:26, 04:31)], [walee(05:09)])
- Investigate why Eliza's framework is not working on certain systems. (mentioned by [RonnySeibt (04:37), jubilant_fox_10717(05:26)])
- Explore hosting options for the project, possibly using a VPS. (mentioned by [shrigma male (04:38), labmgr (05:19)], [wojt175(06:21)])
- Provide guidance on how to interact with the Discord bot and connect it to an agent. (mentioned by [Roque (04:39), 7OROY(05:21)])
- Investigate image generation capabilities of Eliza's framework and provide guidance on enabling it. (mentioned by [Tony AI Champ (04:39), jubilant_fox_10717(05:26)])
- Assist with setting up Eliza's framework on a Windows machine. (mentioned by [jubilant_fox_10717 (04:39), wojt175(06:28)])
- Resolve CUDA toolkit error on Windows (mentioned by @Noah)
- Connect Llama model agent to Discord bot (mentioned by Roque)
- Developer to assist bacon with bot building issues (mentioned by [kbrownfitness](07:04))
- Investigate and resolve database issue for 0xInBeta's bot (mentioned by [0xInBeta](07:12))
- Resolve rate limiting issue with Claude API (mentioned by kbrownfitness)

### Documentation Needs
- Clarify the bounty request and how Eliza can be integrated into it. (mentioned by [! ! ! Lewpik (04:39, 05:06)], [7OROY(05:21)])
- Help with knowledge training for kbrownfitness' use case (mentioned by kbrownfitness)

### Feature Requests
- Implement upload images to tweet feature using agent-twitter-client. (mentioned by dweedify)
- Investigate Twitter API integration for bot (mentioned by @yeboahsvolley)
- Consider using a different model provider for API interaction, as openai's free version is limited (mentioned by [bacon](07:09))