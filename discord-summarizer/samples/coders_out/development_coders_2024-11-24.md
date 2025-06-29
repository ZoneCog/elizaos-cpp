# 💻-coders 2024-11-24

## Summary
Discussed technical issues related to the Twitter scraper and setting up Eliza. Key solutions included fixing adapter-sqlite issue, resolving filename mismatch in twitter-scraper package, using starter kits for easier setup of eliza.

## FAQ
- How to add knowledge reference in Eliza? Does it refer only within character file or also a txt version inside the character file? (asked by @björn)
- Can someone help me with setting up Eliza as I have no experience with Node and am facing problems? (asked by @rhitik)
- Do I need to install CUDA for Model GPU support? (asked by @Modeo)
- Where does the fine-tuning fit into agent creation process? (asked by @coinwitch (ai16z intern))
- Can I fine-tune/train GPT4o on my data using Assistant and have a private Hugging Face service host it for me? API access needed. What are the alternatives without owning GPUs? (asked by @coinwitch)
- Can you provide examples of adding plugins, specifically Solana integrations or client platforms like Twitter/Discord/Telegram? (asked by @leonprou | Ensemble)
- How to get data from tweets, articles and pdf into the agent using Claude? 🤔 #AIChatbotDevelopment (asked by @coinwitch (ai16z intern))
- What should I pull for my discord bot integration with replicate? (asked by [MetaMike])
- How can I reset our SQLite database? Who answered: @Drew (asked by @LiveTheLifeTV)
- What command did you run to do a pull rebase and get the latest build working? (asked by @devAlex.ᴱᵀᴴ)

## Who Helped Who
- @leonprou | Ensemble helped @rhitik with Setting up Eliza by providing Shared starter-kit for setup of eliza.
- @kiziamizia | Cookie3 helped @coinwitch (ai16z intern) with Integration with x platform by providing @Sliph explained how to format X cookies in .env file
- @coinwitch helped Finding alternatives for fine-tuning GPT4o without owning GPUs and exploring external services like RunPod. with Providing information on alternative options, suggesting to consider adding context with sample datasets by providing @kiziamizia
- [kungfumode] helped [MetaMike] with Discord bot integration issue by providing @kiziamizia | Cookie3 provided a suggestion to use RunPod and estimate needs around $50.
- @Drew helped @MetaMike with SQLite issue resolution by providing LiveTheLifeTV shared their experience with resolving SQLite issues, which helped Drew understand that they might be running on an outdated version.
- @DorianD helped @Brandon | Apollo DAO and others interested in exploring new tools. with Explore AgentK for potential use cases within the community's projects. This could lead to more efficient automation of tasks, reducing manual workload by providing @DorianD provided insights on using AgentK for automation tasks, which could potentially alleviate the tedious sys admin work mentioned by @Moths(!).
- @devAlex helped @J3r with Node Version Issue Resolution by providing devAlex.ᴱᵀᴾ helped J3r with node version issues by suggesting the use of cursor.
- @DorianD helped @Brandon | Apollo DAO with Local Development Environment Setup by providing DorianD offered help to Brandon | Apollo DAO for setting up local development environment, sharing personal experience with mac os and imac from 2016.
- @Brandon | Apollo DAO helped @DorianD with Switching versions for better compatibility with Supabase instance by providing @Brandon | Apollo DAO helped @DorianD by suggesting to switch version and providing the command.
- @agent is live on Farcaster @yoinker helped @Brandon | Apollo DAO with Resolved eliza-starter error by switching to main implementation by providing @0xM1M3

## Action Items

### Technical Tasks
- Fix adapter-sqlite issue for Eliza after updating main. (mentioned by @0xflick)
- Install CUDA for proper Model GPU support (mentioned by @Modeo)
- Fine-tune/train GPT4o on custom data using Assistant (mentioned by @coinwitch)
- Custom RunPod integration with Docker and dashboard to toggle agents online/offline. (mentioned by [NplusM])
- Reset SQLite database (mentioned by LiveTheLifeTV)
- Set up initial database environment (mentioned by @Brandon | Apollo DAO)
- Edit searchMemoriesByEmbedding method to use cursor for better performance (mentioned by @devAlex)
- Switch to v0.1.3 release (mentioned by @Brandon | Apollo DAO)
- Update open farcaster PR #386 to use neynar (mentioned by @sayangel)
- Improve memory handling for Discord agent interactions across channels (mentioned by [DorianD](https://discordapp.com/@u/123456))

### Documentation Needs
- Resolve filename mismatch in twitter-scraper-finetune package.json and src/blog (mentioned by @coinwitch (ai16z intern))
- Integrate X-Client-Transaction-Id into .env file format. (mentioned by @Sliph)
- Explore external services for GPU usage in model training, e.g., RunPod. (mentioned by @kiziamizia)
- Switch to stable version of the project if necessary. (mentioned by  LiveTheLifeTV)
- Provide a guide or resources on setting up local development environment, specifically addressing issues with `eliza` and `eliza-starter` projects. (mentioned by @Brandon | Apollo DAO)
- Update documentation for latest version and known issues. (mentioned by )
- Switch from exported class to type in DirectClient implementation. (mentioned by @Brandon | Apollo DAO)
- Resolve documentation error for 'eliza/plugin-image-generation' package (mentioned by [0xM1M3](https://discordapp.com/@u/987654))

### Feature Requests
- Add tweets as context dataset for prompt (mentioned by [kiziamizia | Cookie3])
- Explore AgentK and Splintertree for potential use in automation tasks. (mentioned by @DorianD)