# 💻-coders 2024-11-21

## Summary
The main technical discussions revolved around an error with the `twitter` client and a JSON parsing problem when running start command after recloning dependencies.

## FAQ
- What is the main goal of Obsidian integration? Is it training Faiss on markdown files for embeddings? (asked by @devnextdoor)
- Has anyone encountered an intermittent error from `twitter` client where authentication succeeds but then errors out with 'Error getting user ID: Error: User not found.' ? (asked by @el.gatore)
- Can someone help me resolve the new JSON parsing issue after recloning and installing dependencies? (asked by @only1)
- Any fixes for the issue with type defs not available? (T3L;DR: try both main el repo and packages shipped today.) - TS error when using dompurify package. (asked by only1)
- Can someone provide an example of their .env file used in XAI's API, as I keep getting errors? (I am a beginner). (asked by zing)
- What's the workaround for blocked access on Railway? What causes ERR_USE_AFTER_CLOSE error when using Telegram client with Twitter settings in Dockerfile? How to prevent chat interface from starting incorrectly? (asked by thebishop)
- How do I install local llama and what are cookie.json files used for? (asked by 18 Rabbit)
- How to fix 'DirectClient' type error?, (asked by @ai16z/agent)
- Did you get memory working with database yet? Answered by: @Galego (asked by @maz)
- How to use cookie string in .env file? (asked by @infi)

## Who Helped Who
- @el.gatore helped @only1 with Resolving intermittent twitter login issue by providing el.gatore provided a potential solution for Twitter client error by suggesting `pnpm add -D @types/dompurify`.
- coinwitch helped zing with Setting up SSH extension on VSCode for Eliza directory. by providing Provided document about server security best practices.
- collect helped DorianD with Fixing Telegram chat issue on Railway by providing Collect provided a solution by removing interactive terminal code in index.ts, added process event listener to keep Node.js running without interaction.
- Havohej, DorianD and RL. helped @ai16z/agent with Twitter scrapper issue with 'missing data' error. by providing Troubleshooting Twitter scraper auth failure
- @SlKzᵍᵐ, @coinwitch (ai16z intern) helped @kbrownfitness with Creating a community structure to help newcomers by providing Discussion about creating separate coders channels for beginners and experienced users
- @SlKzᵍᵐ helped @infi with Fixing cookie issue in .env file by providing Provided syntax for TWITTER_COOKIES variable.
- @Tchouston (04:59) helped @infi(04:51) with Twitter Login Issue by providing Resolved Twitter login issue
- @galego helped kbrownfitness (04:53) with Supabase setup by providing Galego provided help to a member with about a decade of IT experience in related fields, offering assistance for setting up Supabase.
- [Galego](05:01) helped General Discord community with Improving Documentation Quality by providing Galego suggested the use of AI to improve documentation quality.
- @Galego helped @björn with Documentation Needs by providing Galego provided a link (@björn) for the schema files needed in adapter-postgres package integration. This helped björn identify which schemas are necessary and where they can be found.

## Action Items

### Technical Tasks
- Investigate intermittent error from `twitter` client (mentioned by el.gatore)
- Added to `/packages/plugin-trustdb` (mentioned by @el.gatore)
- Fix for interactive terminal chat issue on Railway (mentioned by collect)
- Fix 'DirectClient' type error (mentioned by @ai16z/agent)
- Improve image generation for bots (mentioned by @kbrownfitness)
- Update .env syntax for TWITTER_COOKIES (mentioned by @SlKzᵍᵐ)
- Resolve Twitter login issue (mentioned by @Tchouston)
- Connect repo to Supabase (mentioned by @björn)
- Implement AI-assisted writing tools to improve documentation quality. (mentioned by [Galego](05:01))
- Use Supabase via Postgres connection string (mentioned by @Galego)

### Documentation Needs
- Create a PR for the fix if not already done. (mentioned by @0xwarptic)
- Update defaultCharacter or character.json files and .env to interact with Twitter (mentioned by DorianD)
- Use v0.1.3 version of the software. (mentioned by @RL)
- Add more logs for debugging at Twitter part of the code. (mentioned by RL (04:51))
- Update node version documentation for new contributors (mentioned by [SlKzᵍᵐ](05:00))

### Feature Requests
- Resolve 'Error fetching response: SyntaxError' issue when running start command. (mentioned by only1)
- Create separate Discord channel for advanced users beyond basic install and run steps. (mentioned by RL)
- Refine bot engagement farming (interacting/liking other tweets) (mentioned by @kbrownfitness)
- Develop beginner support channels and knowledge base for compounding returns. (mentioned by @pillhead)
- Investigate and resolve the recurring issue with node version compatibility (mentioned by [kbrownfitness](05:06))