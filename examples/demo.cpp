#include "elizaos/core.hpp"
#include "elizaos/agentloop.hpp"
#include <iostream>
#include <memory>

using namespace elizaos;

// Example step function that processes messages
std::shared_ptr<void> processMessage(std::shared_ptr<void> context) {
    static int messageCount = 0;
    messageCount++;
    
    std::cout << "Processing message #" << messageCount << std::endl;
    
    // In a real implementation, this would process actual agent messages
    return context;
}

// Example step function with access to loop control
std::shared_ptr<void> monitorSystem(std::shared_ptr<void> context, AgentLoop* loop) {
    static int monitorCount = 0;
    monitorCount++;
    
    std::cout << "System monitor check #" << monitorCount << std::endl;
    
    // Example: pause after 5 iterations
    if (monitorCount >= 5) {
        std::cout << "Pausing system for demonstration..." << std::endl;
        loop->pause();
    }
    
    return context;
}

int main() {
    std::cout << "ElizaOS C++ Implementation Demo" << std::endl;
    std::cout << "================================" << std::endl;
    
    // Create agent configuration
    AgentConfig config{
        "demo-agent-001",
        "DemoAgent",
        "A demonstration agent showcasing C++ implementation",
        "Created to demonstrate the ElizaOS C++ conversion",
        "efficient"
    };
    
    // Create agent state
    State agentState(config);
    
    // Add some sample data
    Actor user{"user-1", "Demo User", "A user interacting with the demo"};
    agentState.addActor(user);
    
    Goal goal{"goal-1", "Demonstrate C++ functionality", "active", 
              std::chrono::system_clock::now(), std::chrono::system_clock::now()};
    agentState.addGoal(goal);
    
    // Create sample memory
    auto memory = std::make_shared<Memory>(
        "msg-demo-1", 
        "Hello from C++ implementation!", 
        "user-1", 
        config.agentId
    );
    agentState.addRecentMessage(memory);
    
    std::cout << "Agent: " << agentState.getAgentName() << std::endl;
    std::cout << "Bio: " << agentState.getBio() << std::endl;
    std::cout << "Recent messages: " << agentState.getRecentMessages().size() << std::endl;
    std::cout << "Goals: " << agentState.getGoals().size() << std::endl;
    std::cout << std::endl;
    
    // Create agent loop with steps
    std::vector<LoopStep> steps = {
        LoopStep(processMessage),
        LoopStep(monitorSystem)
    };
    
    AgentLoop loop(steps, false, 0.5); // 500ms interval between steps
    
    std::cout << "Starting agent loop..." << std::endl;
    loop.start();
    
    // Let it run for a while
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    if (loop.isPaused()) {
        std::cout << "Loop is paused. Stepping manually..." << std::endl;
        loop.step();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        loop.step();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    std::cout << "Stopping agent loop..." << std::endl;
    loop.stop();
    
    std::cout << "Demo completed successfully!" << std::endl;
    return 0;
}