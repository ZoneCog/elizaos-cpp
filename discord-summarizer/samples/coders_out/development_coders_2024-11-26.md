# 💻-coders 2024-11-26

## Summary
Discussion focused primarily on technical support for ai16z codebase contributions, troubleshooting 'pnpm start' command issues and setting up TWITTER_COOKIES environment variable. EdwardLazz provided guidance to community members.

## FAQ
- What should I do when encountering an error with the 'pnpm start' command and saying hello? What is wrong in my character file path or settings? (asked by @bigxiang)
- How to correctly format TWITTER_COOKIES environment variable as a JSON string, without outer brackets. Can you provide an example with placeholders replaced by actual values? (asked by @FattyBagz)
- How can I enable my bot to trade on base? What files would need configuring in Eliza and what are the steps involved? (asked by Bel)
- 'TWITTER_COOKIES' environment variable formatting issue. How should it be formatted as a valid JSON string, including escaping quotes properly? What to do if issues persist after fixing this?' (asked by @EdwardLazz)
- Is temperature configurable in character and how can I set the model using `character.json` file? (asked by void(null))
- 'model' parameter not passing TypeScript types, what could be causing this issue? How to resolve it?' (asked by @EdwardLazz)
- How can I configure my Argent wallet to execute a swap? What are the steps involved and any specific details or code examples needed for implementation? (asked by @EdwardLazz)
- Any other way to install wsl besides catastrophic failure? Any fix for it? (asked by @RZ)
- catastrophic failure when trying to use wsl. any alternative or how do i get rid of this error ? (asked by @Bel)
- Is there an API for Solana trending tokens? How can I get defined data on them? (asked by AlexAstro)

## Who Helped Who
- @EdwardLazz helped @bigxiang with Troubleshooting pnpm startup issue by providing @EdwardLazz helped bigxiang troubleshoot the 'pnpm start' command and provided guidance on checking error messages and character file paths.
- EdwardLazz helped Bel with Trading Bot Setup by providing Guided user on setting up API credentials and installing required libraries for trading actions.
- EdwardLazz helped Bel with API Call Configuration by providing Provided guidance to configure Eliza's codebase properly by modifying specific files, ensuring API calls are handled correctly and securely.
- @EdwardLazz helped @fudme with Technical Tasks by providing Provide guidance on setting up API credentials, installing required libraries like axios, implementing Swap function in JavaScript.
- @CaptainCool helped @Bel with Correct the '[object Object]' error by replacing it with actual API key. by providing EdwardLazz provided a JSON structure correction for HEURIST plugin in `character.json`.
- @Bel helped @CaptainCool and @RZ with Add the provided validation logic before creating PublicKey. by providing EdwardLazz guided Bel to implement validation check for `contractAddress` in Eliza codebase.
- @EdwardLazz helped Bel with  by providing Navigating to provider files and searching keywords like 'PublicKey' or 'recommendations'. 
- @EdwardLazz helped @Bel with Addressing base58 error and tweet content formatting by providing EdwardLazz provided guidance on validating contract addresses, incorporated validation logic into 'evaluators/trust.ts', suggested logging for debugging purposes.
- @dnx helped @Bel with  by providing Recommended using bitquery as a resource, mentioned 'dexscreeners' to Bel by @dnx.
- @0xM1M3 helped @dnx with Database Configuration by providing @EdwardLazz provided guidance on PostgreSQL adapter usage issue and suggested troubleshooting steps.

## Action Items

### Technical Tasks
- Contribute to ai16z codebase (mentioned by @VI)
- Debug common failure points for initializing Twitter client: invalid credentials, network issues, API rate limits, outdated library versions and environment variables. Share findings. (mentioned by @FattyBagz)
- Resolve Twitter client initialization issue by setting up API credentials, installing required libraries (axios or fetch), creating trading functions for buy/sell actions with proper error handling. (mentioned by EdwardLazz)
- Configure Eliza to properly handle API calls by modifying the following files: src/api/index.js, src/config/config.js and create a trading plugin in src/plugins/trading.js. (mentioned by EdwardLazz)
- Format the TWITTER_COOKIES environment variable as valid JSON string with proper escaping of quotes and no trailing commas. Example: 'TWITTER_COOKIES='[{ (mentioned by EdwardLazz)
- Set up API credentials for exchange and install required libraries like axios. (mentioned by @fudme)
- Add validation check for 'contractAddress' before creating a PublicKey to prevent Base58 error. (mentioned by @EdwardLazz)
- Correct the JSON structure in `character.json` by replacing '[object Object]' with actual API key for HEURIST plugin. (mentioned by @CaptainCool)
- Implement validation check in the appropriate file within Eliza codebase, likely `plugin-solana/src/index.js`. (mentioned by @EdwardLazz and @Bel)
- Locate provider files for processing recommendations (mentioned by @EdwardLazz)
- Validate contract addresses before creating PublicKey instances to resolve base58 errors. (mentioned by @EdwardLazz)
- Incorporate address validation logic in 'evaluators/trust.ts' file where recommendations are processed, and log addresses for debugging purposes. (mentioned by @EdwardLazz)
- Format tweet content dynamically based on recommendation details to include conviction level and token ticker in agent's tweets. Implement this logic where recommendations are handled. (mentioned by @EdwardLazz)
- Investigate PostgreSQL adapter usage issue (mentioned by @0xM1M3)

### Documentation Needs
- Provide correct format of TWITTER_COOKIES environment variable as JSON string, without outer brackets. Replace placeholders with actual values. (mentioned by @FattyBagz)
- Configure Argent wallet to execute a swap (mentioned by @EdwardLazz)

### Feature Requests
- Troubleshoot 'pnpm start' command for bigxiang with error message and character file path verification. (mentioned by @bigxiang)
- Align Eliza's codebase with Virtuals.io by reviewing architectural decisions, API integration compatibility and data structures for consistency. (mentioned by EdwardLazz)
- Add validation check to ensure PublicKey is not null or empty before creating a transaction. (mentioned by @Bel)
- Consider using bitquery for enhanced recommendation data and explore 'dexscreeners' as an additional resource. (mentioned by @dnx)