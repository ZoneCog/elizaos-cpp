# 💻-coders 2024-10-28

## Summary
The discussion focused on using 'twikit' library to scrape tweets as an alternative method. The feasibility of a Discord bot handling trading and securing funding was questioned, with the conclusion that it is not its intended purpose but rather for general queries/tasks.

## FAQ
- Can the Discord bot handle trading or secure funding? What is its connection to financial crypto stuff? (asked by [DegenSpartan] (00:07))
- Does ai16z project already have a Twitter scraper implemented using 'twikit' library? (asked by [Ophiuchus](00:38))
- Did you guys top up credit for the API in OpenAI to make your bot work? And if so, how much was it and where can I do that too? (asked by [Kevin](01:06))
- Why would we need an alternative for the Twitter API's 7-day limit? Is there a cost associated with extending it beyond this period, or is another approach more viable? (asked by [ferric | stakeware.xyz](01:09))
- What hardware are you running your agent on? What's the setup like? (asked by @SotoAlt | WAWE (01:20))
- Is it possible to train models using data other than tweets, such as writing and podcast transcripts? How much compute power is required for this kind of training? (01:23) (asked by @ferric | stakeware.xyz)
- What's the difference between your character file input method compared to others? (asked by @ferric | stakeware.xyz)
- Are you using OpenAI API or local? Are RTXs needed if ai16z moons? What hardware are u aiming to run this locally for cost calculation and performance comparison? (asked by @SotoAlt | WAWE)
- How do I train the model on my end with hiroP's setup in prod environment, considering prompt caching techniques used by Anthropic as a reference point due to high costs? (asked by @Kevin)
- How can I get the bot to be relevant when Marc is mentioned? What are some alternatives without calling APIs? (asked by [big dookie])

## Who Helped Who
- [DegenSpartan] (00:07) helped [Ophiuchus](00:06) with Understanding project's scope by providing DegenSpartan provided information about the purpose of Discord bot and advised against reverse engineering.
- [ferric | stakeware.xyz] helped Discussing the feasibility of running a local LLM and potential hardware requirements with Providing perspective on resource consumption by local LLMs, suggesting that it may not be practical for all users. by providing [DegenSpartan](01:19)
- @DegenSpartan helped @ferric | stakeware.xyz, @hiroP with Hardware upgrade discussion by providing Discussing hardware requirements and upgrades for better performance (01:20-01:34)
- @DegenSpartan helped All members discussing the need for GPUs and local setup challenges. with Discussed hardware requirements, costs associated with RTX units, prompt caching techniques by providing @ferric | stakeware.xyz helped @hiroP solve issues related to character file repository
- @futjr helped All members with Shared an unrelated but humorous contribution by providing @big dookie shared a bot example using llama model to pull from YouTube playlist
- [hiroP (01:42)] helped [Kevin] with Creating Trump or Tate Character in Bot by providing hiroP provided guidance to Kevin about creating a character file for the bot.
- [hiroP (01:49)] helped [whobody] with Project configuration by providing hiroP provided guidance on configuring project to use correct characterfile
- [SotoAlt | WAWE(02:33) ] helped  with OpenAPI Issue Resolution by providing SotoAlt | WAWE resolved OpenAI API rate limit issue by addressing an IP problem.
- [Kevin] helped [SotoAlt | WAWE] with Fixing 'Too Many Requests' error with OpenAI API. by providing SotoAlt | WAWE helped Kevin to understand the issue and provided guidance on how Eliza should be trained (mentioned at 02:43)
- [SotoAlt | WAWE] helped [Ophiuchus] with 3D Avatar Creation by providing [ferric | stakeware.xyz] provided a GitHub link for characterfile and explained how it can be used in creating avatars.

## Action Items

### Technical Tasks
- Implement an alternative to API for pulling tweets using 'twikit' library (mentioned by [Ophiuchus](00:02))
- Consider using Llama 3.1 or Nemotron to enhance the bot's capabilities (mentioned by [Ophiuchus](00:08))
- Investigate alternative APIs for Twitter data retrieval (mentioned by [ferric | stakeware.xyz](01:09))
- Explore local LLM options and assess feasibility for the project (mentioned by [ferric | stakeware.xyz](01:19))
- Upgrade hardware for better performance (mentioned by @DegenSpartan)
- Wrangle data for ai project (mentioned by @hiroP)
- Implement basic functionality for 'finds Marc talking' feature (mentioned by [big dookie (01:35)])
- Configure project to use correct characterfile (mentioned by [hiroP (01:49)])
- Investigate OpenAI API rate limit issue and IP problem (mentioned by [SotoAlt | WAWE(02:33) ])
- Train Eliza with terminal commands (mentioned by [SotoAlt | WAWE])
- Integrate AI agent into a webapp using DirectClient for HTTP server backend API (mentioned by [SotoAlt | WAWE])
- Explore running smaller models on a laptop with an RTX GPU (mentioned by @SotoAlt)

### Documentation Needs
- Update documentation to include API usage and error handling guidelines for OpenAI (mentioned by [Kevin](01:12, 01:13))
- Fix the Twitter posting code in training script (mentioned by @ferric | stakeware.xyz)
- Share tutorial on the process of wrangling data. (mentioned by @hiroP)
- Deploy bots on Discord platform. (mentioned by [Kevin (01:38)])
- Work on the reo to fix API issue (mentioned by [Kevin (02:43)])

### Feature Requests
- Investigate the possibility of a Discord bot handling trading and securing funding for projects. (mentioned by [DegenSpartan](00:04))
- Consider feature to archive entire profiles using a more efficient method than current approach (mentioned by [Ophiuchus](00:38))
- Archive tweets and train model to create personalized avatar feature in the app. (mentioned by _d3f4ult, DegenSpartan)