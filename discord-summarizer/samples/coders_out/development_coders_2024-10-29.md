# 💻-coders 2024-10-29

## Summary
@big dookie suggested implementing chunking for Twitter context understanding. The discussion also involved training and hosting a fine-tuned Llama model locally with bigger GPU support, which is crucial in enhancing the performance of these models.

## FAQ
- Are most of you using gpt4 + claude, an already fine-tuned llama like Pygmalion or something, or your own fine tuned Llama? Where do you train and host your llama? (asked by @dmg)
- How can I enable the AI Agent to trade tokens in Eliza setup on Discord? (asked by @encrypted)
- Is Jupiter API integration available? What's the goal of creating characters and avatars? (asked by SotoAlt | WAWE)
- Should we focus on quantity or quality for character creation? How many people work at this company, where am I in all these projects? (asked by whobody)
- How to get the 6 seconds of video and last frame for using comfy? What is Lincoln's birthday? How can I make FFmpeg work with moving effects on a static image? (asked by @big dookie)
- How to get the audio-reactivity system shitposting tweets as Gary Andresen and what is his birthday? How can I implement beat matching for low octave sounds in ThreeJS? (asked by @big dookie)
- What can I use with web audio API and an npm package to make glitch effects easier than GD commands? What are some alternatives for image cuts according to music using transient peaks, specifically on a static looped image aiming at lofi-style digital destruction based on amplitude? (asked by [whobody])
- How can I apply glitch effects that move with the waveform without getting too complex? Is it possible to shift layered chroma values using ffmpeg, and how could this be automated in a pipeline process like fluent-ffmpeg? (asked by [big dookie])
- Could you suggest an alternative approach for applying glitch effects on static images based on sound? Would it involve extracting RGB layers of the image and warping/graining them according to audio input, or is there another method? (asked by [Poe])
- Are you building teh prerequisites to make Mairc visible in video? (asked by @big dookie)

## Who Helped Who
- @dmg helped All members in the chat. with Technical guidance on improving AI models by providing @big dookie explained chunking for Twitter context understanding and mentioned training a fine-tuned Llama model locally with bigger GPU support.
- big dookie helped SotoAlt | WAWE with Improving API integration for finding responses by providing big dookie helped SotoAlt | WAWE with the idea of using a bigger llama model after Meta HF approval.
- @big dookie helped @claude with Implement audio-reactivity with moving effects on static image. by providing @whobody suggested using an alternative to FFmpeg, such as Three.js or a different package.
- [big dookie] helped [whobody] with Suggested alternative methods for applying glitch effects on static images based on sound. by providing [Poe]
- [Poe] helped [big dookie] with Shared experience with using Three.js and Web Audio API to achieve similar goals, but expressed interest in simpler solutions for lofi-style effects. by providing [Big Dookie]
- @Poe helped @big dookie with Improve browser-based video saving functionality by providing Poe suggested using cursor for web UI navigation.
- [SotoAlt | WAWE (02:34-02:37)] helped [pastd_] with AI Clone Development by providing Guidance on building an AI clone using openai api and credits or local LLM, hosting options.
- [big dookie (02:45)], [boom lfg] helped [community members] with UX Improvement by providing Improve UX in conversation completion, possibly with help from the community.
- @st4rgard3n helped Lina with Twitter fix by providing St4rgard3N reverted Lina's Twitter to the annoying stage after anti-annoyance fixes broke her account.
- @big dookie helped @futjr with Learning new vocabulary by providing @big dookie taught the word oligopoly to @futjr.

## Action Items

### Technical Tasks
- Implement chunking for Twitter context understanding (mentioned by @big dookie)
- Complete cranking through Eliza's tomorrow (mentioned by whobody)
- Make the system smarter to find actual responses using API integration with Jupiter's services.  (mentioned by big dookie)
- Implement audio-reactivity using an alternative to FFmpeg, possibly ThreeJS (mentioned by @big dookie)
- Explore web audio API with npm package for glitch effects on static images (mentioned by [big dookie])
- Improve browser-based video saving functionality (mentioned by @big dookie)
- Use cursor for tab completion (mentioned by [shaw (02:32)])
- Build an AI clone using openai api and credits or local LLM, host on AWS or locally for testing. (mentioned by [pastd_, SotoAlt | WAWE (02:34-02:37)])
- Deploy an agent using a free node + OAI API for cost-effectiveness (mentioned by @hiroP)
- Dockerize agent for local development on workstation, then run cloud server version when not working. (mentioned by @hiroP)
- Investigate Twitter API costs for potential integration (mentioned by [big dookie, ashxn])

### Documentation Needs
- Train and host a fine-tuned Llama model locally with bigger GPU support. (mentioned by @big dookie)
- Use a bigger llama model for inference/chat after Meta HF approval. (mentioned by big dookie)
- Automate effect application using fluent-ffmpeg in a pipeline process. (mentioned by [big dookie])
- Host the model in TEE and provision containers with private keys never leaving tee (mentioned by @shaw)

### Feature Requests
- Work on original characters/IP and 3D avatars stuff. (mentioned by SotoAlt | WAWE)
- Add beat matching feature for low octave sounds in the audio-reactivity system. (mentioned by @whobody)
- Consider using cursor for web UI navigation and interaction. (mentioned by @Poe)
- Improve UX in conversation completion, possibly with help from the community. (mentioned by [big dookie (02:45)], [boom lfg])
- Consider hosting the bot locally or using an API with associated costs and potential need for a dedicated server (mentioned by [SotoAlt | WAWE, @pastd_, others])