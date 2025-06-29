# 💻-coders 2024-11-13

## Summary
The chat focused on deploying Ollama service in an Amazon Web Services environment. Deniz expressed intent to run the server, while SotoAlt sought successful examples of such a setup. Ophiuchus provided detailed instructions about stopping and starting ollama with desired model settings for AWS deployment.

## FAQ
- Anyone successfully deployed in AWS?? (asked by SotoAlt (WAWE))
- Why is setting up and debugging avoided? What are the challenges faced during setup process? (asked by [SotoAlt | WAWE (ai16z janitor)](00:20))
- What's a straightforward way to quickstart Eliza given current issues with testing locally due to PR not merged yet? (asked by [Deniz](00:34))
- How can I test everything for eliza until the new pr gets merged? What are alternative ways of setting up and running tests in this scenario? (asked by [Harry Touloupas](00:31))
- Why am I getting an error while connecting to Twitter with two different accounts? What can be done about it? (asked by @binye)
- Can Node version 22+ run on Vercel hosting platform for Eliza project requirements? (asked by @ferric_stakeware.xyz)
- Do any of the Eliza Twitter agents use proxies for deployment? Are proxies necessary to run an acc safely? Who answered: @Shannon Code (emblem vault) (asked by @Bootoshi)
- What solutions do you recommend for running an agent on servers instead of local ? What about hosting Ailon on ai16z servers? (asked by @bundo)
- Can I use the Twitter API free version for getting tweets/posting without affecting replies functionality? What do you suggest, @shaw? (02:04-02:05) (asked by @wondering)
- What is the correct way of adding cookies to access Twitter API? (asked by Adnan)

## Who Helped Who
- Ophiuchus helped Deniz (00:12) with Deploy ollama with desired settings for AWS deployment. by providing Ophiuchus provided guidance on deploying Ollama, stopping the service and pulling a new model
- [SotoAlt | WAWE (ai16z janitor)] helped [Ophiuchus] with Technical discussion by providing Discussing AWS EC2 for Eliza project
- [Ophiuchus](00:21) helped  with  by providing [Ophiuchus] provided information about using termux to run langchain locally, but mentioned a desire for production setup
- [Deniz](00:34) helped [Ophiuchus](00:29) with  by providing [Deniz] asked about switching from npx locallama to ollama, and [Ophiuchas] provided insights on using redpill ai & openrouter depending on rate limits
- @ferric helped @binye with Twitter Account Connection Issue by providing Finding alternative solutions to Twitter account issues and discussing potential problems with the current setup.
- @claude helped @bundo with Setting up a server for agent hosting by providing @hiroP suggested using Linode and offered help in setting it up
- ferric | stakeware.xyz (02:04-02:06) helped collect with Resolving authentication error and suggesting Twitter API free version by providing @wondering
- @collect helped [ferric | stakeware.xyz](02:12) with Troubleshooting account image addition problem. by providing @Shannon Code suggested building x like AI agents to solve the issue with adding cover images.
- @Honey B.(02:14) helped @shaw(02:14) with [ferric | stakeware.xyz](02:13) suggested working with Yikes to cut stable releases and adapting the development process. by providing [ferric | stakeware.xyz](02:13) provided guidance on git commands for reverting to older commits.
- ferric | stakeware.xyz helped shaw with Node version update by providing @yikesawjeez wakes up to help with the issue (mentioned by ferric | stakeware.xyz)

## Action Items

### Technical Tasks
- Deploy Ollama on AWS (mentioned by [SotoAlt, Deniz])
- Consider using AWS EC2 for Eliza project (mentioned by [Ophiuchus, SotoAlt])
- Explore the possibility of running on a Raspberry Pi or Tomato for API-based applications (mentioned by [ferric | stakeware.xyz])
- Set up a production environment using Raspberry Pi on phone (mentioned by [Ophiuchus](00:21))
- Investigate alternative hosting solutions for Eliza, considering Node.js version requirements (mentioned by @Leonard)
- Consider using Linode for server hosting (mentioned by @hiroP)
- Investigate Twitter API free version for tweet retrieval without affecting reply functionality. (mentioned by @wondering)
- Develop a p2p chat substrate for AI agents with blockchain wallets. (mentioned by [ferric | stakeware.xyz](02:08))
- Work with Yikes to cut stable releases (mentioned by [ferric | stakeware.xyz](02:13))

### Documentation Needs
- Configure model storage location for ollama (mentioned by Ophiuchus)
- Recover AWS credentials after losing encrypted drive, including SSH keys and password reset process. (mentioned by [Ophiuchus])
- Resolve authentication error: DenyLoginSubtask by checking email and unblock account if necessary (mentioned by Shannon Code (emblem vault))
- Create a funding mechanism for developers to build the p2p chat substrate. (mentioned by [ferric | stakeware.xyz](02:11))
- Adapting development process for faster iterations and breaking things. (mentioned by [ferric | stakeware.xyz](02:13))

### Feature Requests
- Consider switching to mozilla's CPU-friendly model format for llamafiles (mentioned by [Ophiuchus](00:24))
- Work on integrating mozilla's CPU-friendly model format into llamafiles (mentioned by [Ophiuchus](00:29))
- Explore potential issues with Twitter API and account authentication when using multiple accounts on the same platform. (mentioned by @Binye)
- Implement a background thought module in the agent's architecture. (mentioned by @Shannon Code (emblem vault))
- Implement a trust-based scoring system for agents based on ticker suggestions. (mentioned by [ferric | stakeware.xyz](02:11))
- Implement a temporary fix by creating a dev branch for new code (mentioned by [ferric | stakeware.xyz])