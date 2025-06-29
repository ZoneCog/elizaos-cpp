# ElizaOS C++ Implementation Demo

A simple demonstration of the C++ implementation showcasing the core functionality.

## Running the Demo

```bash
# Build with examples enabled
mkdir build && cd build
cmake -DBUILD_EXAMPLES=ON ..
cmake --build .

# Run the demo
./examples/elizaos_demo
```

## Expected Output

```
ElizaOS C++ Implementation Demo
================================
Agent: DemoAgent
Bio: A demonstration agent showcasing C++ implementation
Recent messages: 1
Goals: 1

Starting agent loop...
Processing message #1
System monitor check #1
Processing message #2
System monitor check #2
Processing message #3
System monitor check #3
Processing message #4
System monitor check #4
Processing message #5
System monitor check #5
Pausing system for demonstration...
Loop is paused. Stepping manually...
Processing message #6
Stopping agent loop...
Demo completed successfully!
```

## What the Demo Shows

1. **Agent Configuration**: Creating an agent with identity and bio
2. **State Management**: Adding actors, goals, and recent messages
3. **Agent Loop**: Running a threaded event loop with custom step functions
4. **Pause/Resume**: Demonstrating manual control of the agent loop
5. **Thread Safety**: Safe execution and shutdown

## Code Structure

The demo (`examples/demo.cpp`) demonstrates:

- Core data structures: `AgentConfig`, `State`, `Memory`, `Actor`, `Goal`
- Agent loop functionality: `AgentLoop` with custom step functions
- Thread management: Start, pause, step, and stop operations
- API compatibility: Matching the Python agentloop interface

This showcases the successful Stage 1 implementation of the ElizaOS C++ conversion.