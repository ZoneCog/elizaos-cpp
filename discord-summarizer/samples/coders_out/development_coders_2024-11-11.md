# 💻-coders 2024-11-11

## Summary
. The primary technical discussion revolved around a model-related embedding problem. @hiroP(00:01) reported receiving errors due to embeddings, which was later identified as the issue of an undefined `modelProvider`. Ophiuchus (00:07), proposed switching from main codebase to postgres for resolving this error by calculating embedding distance and parsing JSON messages. Ferric | stakeware.xyz(00:05) also suggested fixing a bug in getCachedEmbeddings.

## FAQ
- I'm getting a model related error but it seems to be due to embedding. Can I see the settings section of a characterfile that works? Please! Could you share this with me? (asked by @hiroP(00:01))
- I'm getting an 'embeddingModel undefined error'. What could be causing it and how can I fix the issue? (asked by @hiroP(00:03))
- What should I do for the latest version of embeddings? Can you guide me on setting up modelProvider in .env or characterfile correctly with OAi key included? (asked by @hiroP)
- Can we discuss more about what's not working and the error message related to embeddings? Are there specific models/libraries causing issues or any debugging steps taken so far? (asked by @Ophiuchus, @Eliza)
- 'how do i force a rebuild of adapter-sqlite?' and 'why isn't pnpm run --rebuild working on Node v23?' (asked by [ferric | stakeware.xyz])
- What is not working with the embeddings, which model or library are you using? (asked by [Eliza (00:15)])
- 'what value u are getting for console.log(\ (asked by [Ophiuchus](00:43))
- do we need to migrate to postgres or some other DB? (asked by [Dorian] (01:26))
- im using openai api, might check that (asked by [SotoAlt | WAWE](01:23))
- How was the SQLite bug handled? (link to PR #261) (asked by [Dorian](01:52))

## Who Helped Who
- @hiroP(00:03) helped All members of the chat discussing embeddings issue. with Debugging and fixing an error related to undefined 'embeddingModel' in main codebase by providing @Ophiuchus (00:07) provided a solution to switch from main codebase to postgres for embedding distance calculation & JSON parsing
- @Ophiuchus, @Eliza helped @SotoAlt | WAWE with Setting correct environment variables and characterfile settings to resolve embeddings issues. by providing @hiroP received guidance on setting up modelProvider with OPENAI for embedding
- [Dorian] helped [shaw, ferric | stakeware.xyz] with Configuring model provider name by providing 'openai' should be used in JSON configuration for ModelProviderName.
- [Ophiuchus](00:41) helped [All] with Technical Discussion by providing .env.example file mentioned for USE_OPENAI_EMBEDDING setting
- [ferric | stakeware.xyz](01:47) helped [Dorian, SotoAlt | WAWE] with SQLite issue related to OpenAI embeddings. by providing ferric fixed a SQLite bug and updated the codebase.
- @ferric | stakeware.xyz helped bot with voice message issue, suggested '/leavechannel' command to leave the problematic channel. with Provided solution for bot overwhelmed by Discord voice messages by providing @SotoAlt | WAWE
- @hiroP helped bot tweeting issue, suggested checking interactions every 15-20 minutes and limiting to two tweets per day. with Provided advice on managing Twitter bot's interaction frequency by providing @SotoAlt | WAWE
- shaw helped hiroP with Understanding permission issues in a deleted channel. by providing Shaw explained the Discord error message.
- @slim (05:21) helped  with Setting Up Environment by providing Slim provided guidance on setting up environment, adding OpenAI key and SQLite setup.
- [0x𝒲𝒶𝓁𝒸𝒽] (6:15-7) helped [ferric | stakeware.xyz] with Debugging and fixing TypeError in Twitter client code by providing Explained TypeError and provided a solution

## Action Items

### Technical Tasks
- Fix main code causing embedding model undefined error (mentioned by [ferric | stakeware.xyz](00:05))
- Debug and fix getCachedEmbeddings bug in main code (mentioned by [ferric | stakeware.xyz](00:05))
- Set modelProvider to use OPENAI (mentioned by @hiroP)
- Resolve JSON parsing error for adapter-sqlite rebuild on Node v23 (mentioned by [ferric | stakeware.xyz])
- Set embedding model to 'text-embedding-3-small' (mentioned by [Ophiuchus](00:41))
- Check .env.example for USE_OPENAI_EMBEDDING setting (mentioned by [Ophiuchus](00:41))
- Review error handling for 'Too few parameter values were provided' in SqliteDatabaseAdapter (mentioned by [SotoAlt | WAWE](01:02))
- Consider migrating to PostgreSQL or another DB if issues persist with SQLite (mentioned by [SotoAlt | WAWE](01:12))
- Fix SQLite bug related to OpenAI embeddings (mentioned by [ferric | stakeware.xyz](01:47))
- Create video tutorial for Discord input bug (mentioned by @Ophiuchus)
- Revisit LLAMA issues related to GPU, CUDA (mentioned by slim)
- Debug Discord version switch and interaction with Twitter bot. (mentioned by hiroP)
- Deploy agents on AWS or other hosting platforms (mentioned by @SotoAlt | WAWE)
- Fix TypeError: cookiesArray.map is not a function (mentioned by [0x𝒲𝒶𝓁𝒸𝒽] (6:15-7))

### Documentation Needs
- Update .env and characterfile with OAi key for embeddings (mentioned by @Ophiuchus, @Eliza)
- Update ModelProviderName to 'openai' in JSON configuration for custom characters and defaultCharacter. (mentioned by [Dorian, shaw])
- Update documentation for the fix in PR #261 on GitHub. (mentioned by [ferric | stakeware.xyz](01:54))
- Ensure 'clients' include Discord in character.json file for proper response generation. (mentioned by @Deniz)

### Feature Requests
- Switch to postgres for embedding distance calculation and JSON parsing. (mentioned by [Ophiuchus (00:07)])
- Implement '/leavechannel' command to leave voice channels in bots. (mentioned by @SotoAlt | WAWE)