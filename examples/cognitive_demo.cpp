#include "elizaos/core.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

using namespace elizaos;

// Example implementation of a simple symbolic reasoner
class SimpleSymbolicReasoner : public SymbolicReasoner {
public:
    std::string getName() const override {
        return "SimpleReasoner";
    }
    
    std::vector<std::string> reason(const State& state, const std::string& query) override {
        std::vector<std::string> results;
        
        // Simple rule-based reasoning
        if (query.find("hello") != std::string::npos) {
            results.push_back("Greeting detected - respond with greeting");
        }
        if (query.find("help") != std::string::npos) {
            results.push_back("Help request detected - provide assistance");
        }
        if (query.find("time") != std::string::npos) {
            results.push_back("Time query detected - provide current time");
        }
        
        // Use agent context
        if (!state.getActors().empty()) {
            results.push_back("Multiple actors present - consider social context");
        }
        
        return results;
    }
    
    bool validateRule(const std::string& rule) const override {
        return !rule.empty() && rule.length() > 3;
    }
    
    void addRule(const std::string& rule) override {
        if (validateRule(rule)) {
            rules_.push_back(rule);
        }
    }
    
private:
    std::vector<std::string> rules_;
};

// Example implementation of a simple connectionist processor
class SimpleConnectionistProcessor : public ConnectionistProcessor {
public:
    std::string getName() const override {
        return "SimpleEmbedder";
    }
    
    EmbeddingVector generateEmbedding(const std::string& input) override {
        // Simple character-based embedding
        EmbeddingVector embedding(5, 0.0f);
        
        for (char c : input) {
            embedding[0] += (c >= 'a' && c <= 'z') ? 0.1f : 0.0f;  // lowercase letters
            embedding[1] += (c >= 'A' && c <= 'Z') ? 0.1f : 0.0f;  // uppercase letters
            embedding[2] += (c >= '0' && c <= '9') ? 0.1f : 0.0f;  // digits
            embedding[3] += (c == ' ') ? 0.1f : 0.0f;              // spaces
            embedding[4] += 0.05f;                                 // total length factor
        }
        
        return embedding;
    }
    
    double computeSimilarity(const EmbeddingVector& a, const EmbeddingVector& b) override {
        if (a.size() != b.size()) return 0.0;
        
        double dot_product = 0.0;
        double norm_a = 0.0, norm_b = 0.0;
        
        for (size_t i = 0; i < a.size(); ++i) {
            dot_product += a[i] * b[i];
            norm_a += a[i] * a[i];
            norm_b += b[i] * b[i];
        }
        
        if (norm_a == 0.0 || norm_b == 0.0) return 0.0;
        return dot_product / (std::sqrt(norm_a) * std::sqrt(norm_b));
    }
    
    std::vector<std::string> generateResponse(const EmbeddingVector& context) override {
        std::vector<std::string> responses;
        
        // Generate responses based on embedding characteristics
        if (context.size() >= 5) {
            if (context[0] > 1.0) responses.push_back("Text contains many lowercase letters");
            if (context[1] > 0.5) responses.push_back("Text contains uppercase letters");
            if (context[2] > 0.3) responses.push_back("Text contains numbers");
            if (context[3] > 0.5) responses.push_back("Text has multiple words");
        }
        
        return responses;
    }
};

// Example task worker for demonstration
class ExampleTaskWorker : public TaskWorker {
public:
    std::string getName() const override {
        return "ExampleWorker";
    }
    
    bool validate(const Task& task, const State& state, std::shared_ptr<Memory> message) const override {
        (void)state; (void)message; // Mark as intentionally unused
        // Simple validation - task should have description
        return !task.getDescription().empty();
    }
    
    bool execute(Task& task, State& state, const TaskOptions& options) override {
        (void)state; (void)options; // Mark as intentionally unused
        std::cout << "Executing task: " << task.getName() << std::endl;
        std::cout << "Description: " << task.getDescription() << std::endl;
        
        // Simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        std::cout << "Task completed successfully!" << std::endl;
        return true;
    }
};

int main() {
    std::cout << "=== ElizaOS C++ Cognitive Primitives Demo ===" << std::endl << std::endl;
    
    // 1. Enhanced Memory Demonstration
    std::cout << "1. Enhanced Memory System:" << std::endl;
    
    AgentConfig config{
        "demo-agent-001",
        "DemoAgent",
        "A demonstration agent showcasing cognitive primitives",
        "Created to demonstrate the advanced cognitive architecture",
        "demonstrative"
    };
    
    // Create enhanced memory with metadata and embeddings
    MessageMetadata metadata;
    metadata.source = "demo";
    metadata.scope = MemoryScope::PRIVATE;
    metadata.tags = {"demo", "cognitive", "primitives"};
    
    auto memory = std::make_shared<Memory>(
        "demo-memory-001",
        "Hello, I need help with cognitive tasks",
        "user-001",
        config.agentId,
        metadata
    );
    
    // Add embedding
    EmbeddingVector embedding = {0.8f, 0.2f, 0.1f, 0.9f, 0.5f};
    memory->setEmbedding(embedding);
    memory->setSimilarity(0.95);
    
    // Add hypergraph connections
    memory->addHypergraphNode("concept-help");
    memory->addHypergraphNode("concept-cognitive");
    memory->addHypergraphEdge("relation-request");
    
    std::cout << "  Memory ID: " << memory->getId() << std::endl;
    std::cout << "  Content: " << memory->getContent() << std::endl;
    std::cout << "  Embedding dimensions: " << memory->getEmbedding()->size() << std::endl;
    std::cout << "  Similarity score: " << memory->getSimilarity() << std::endl;
    std::cout << "  Hypergraph nodes: " << memory->getHypergraphNodes().size() << std::endl;
    std::cout << "  Hypergraph edges: " << memory->getHypergraphEdges().size() << std::endl;
    std::cout << std::endl;
    
    // 2. Hypergraph Structure Demonstration
    std::cout << "2. Hypergraph Knowledge Representation:" << std::endl;
    
    HypergraphNode conceptNode("node-help", "HelpConcept");
    conceptNode.setAttribute("category", "user_request");
    conceptNode.setAttribute("importance", "high");
    
    std::vector<UUID> relationNodes = {"node-help", "node-cognitive", "node-agent"};
    HypergraphEdge relationEdge("edge-assists", "AssistsRelation", relationNodes);
    relationEdge.setWeight(0.85);
    
    std::cout << "  Node: " << conceptNode.getLabel() << " (ID: " << conceptNode.getId() << ")" << std::endl;
    auto categoryAttr = conceptNode.getAttribute("category");
    if (categoryAttr) {
        std::cout << "    Category: " << categoryAttr.value() << std::endl;
    }
    std::cout << "  Edge: " << relationEdge.getLabel() << " (Weight: " << relationEdge.getWeight() << ")" << std::endl;
    std::cout << "    Connects " << relationEdge.getNodeIds().size() << " nodes" << std::endl;
    std::cout << std::endl;
    
    // 3. Task Orchestration Demonstration
    std::cout << "3. Task Orchestration System:" << std::endl;
    
    TaskManager taskManager;
    auto worker = std::make_shared<ExampleTaskWorker>();
    taskManager.registerWorker(worker);
    
    // Create and schedule tasks
    UUID taskId1 = taskManager.createTask("ExampleWorker", "Process user greeting");
    UUID taskId2 = taskManager.createTask("ExampleWorker", "Analyze cognitive request");
    
    auto task1 = taskManager.getTask(taskId1);
    auto task2 = taskManager.getTask(taskId2);
    
    task1->addTag("queue");
    task1->addTag("immediate");
    task1->setPriority(10);
    
    task2->addTag("queue");
    task2->setPriority(5);
    
    std::cout << "  Created task 1: " << task1->getName() << " (Priority: " << task1->getPriority() << ")" << std::endl;
    std::cout << "  Created task 2: " << task2->getName() << " (Priority: " << task2->getPriority() << ")" << std::endl;
    
    // Start task manager and let it run briefly
    taskManager.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    taskManager.stop();
    
    std::cout << std::endl;
    
    // 4. Cognitive Fusion Engine Demonstration
    std::cout << "4. Symbolic/Connectionist Fusion Engine:" << std::endl;
    
    CognitiveFusionEngine fusionEngine;
    State agentState(config);
    
    // Add some actors to the state
    Actor user{"user-001", "DemoUser", "A user interacting with the system"};
    Actor assistant{"assistant-001", "Assistant", "Helpful AI assistant"};
    agentState.addActor(user);
    agentState.addActor(assistant);
    
    // Register cognitive components
    auto symbolicReasoner = std::make_shared<SimpleSymbolicReasoner>();
    auto connectionistProcessor = std::make_shared<SimpleConnectionistProcessor>();
    
    fusionEngine.registerSymbolicReasoner(symbolicReasoner);
    fusionEngine.registerConnectionistProcessor(connectionistProcessor);
    
    // Integrate memory into fusion engine
    fusionEngine.integrateMemory(memory);
    
    // Process a query using hybrid reasoning
    std::string query = "Hello, can you help me with time management?";
    auto result = fusionEngine.processQuery(agentState, query);
    
    std::cout << "  Query: " << query << std::endl;
    std::cout << "  Symbolic Results (" << result.symbolicResults.size() << "):" << std::endl;
    for (const auto& res : result.symbolicResults) {
        std::cout << "    - " << res << std::endl;
    }
    
    std::cout << "  Connectionist Results (" << result.connectionistResults.size() << "):" << std::endl;
    for (const auto& res : result.connectionistResults) {
        std::cout << "    - " << res << std::endl;
    }
    
    std::cout << "  Confidence Score: " << result.confidence << std::endl;
    std::cout << "  Total Fused Results: " << result.fusedResults.size() << std::endl;
    
    // Test memory retrieval
    auto relevantMemories = fusionEngine.retrieveRelevantMemories("help", 3);
    std::cout << "  Retrieved " << relevantMemories.size() << " relevant memories" << std::endl;
    
    std::cout << std::endl;
    
    // 5. Integration Example
    std::cout << "5. System Integration Example:" << std::endl;
    
    // Create a complex scenario combining all systems
    auto cognitiveMemory = std::make_shared<Memory>(
        "cognitive-integration-001",
        "System integration test for cognitive primitives",
        "system-001",
        config.agentId
    );
    
    // Add rich metadata and connections
    CustomMetadata customMeta;
    customMeta.customData["integration_level"] = "high";
    customMeta.customData["system_test"] = "true";
    cognitiveMemory->setMetadata(customMeta);
    
    auto integration_embedding = connectionistProcessor->generateEmbedding(cognitiveMemory->getContent());
    cognitiveMemory->setEmbedding(integration_embedding);
    
    // Create integration task
    UUID integrationTaskId = taskManager.createTask("ExampleWorker", "Demonstrate cognitive integration");
    auto integrationTask = taskManager.getTask(integrationTaskId);
    integrationTask->addTag("integration");
    integrationTask->addTag("demo");
    
    TaskOptions taskOptions;
    taskOptions.data["memory_id"] = cognitiveMemory->getId();
    taskOptions.data["fusion_enabled"] = "true";
    integrationTask->setOptions(taskOptions);
    
    // Integrate with fusion engine
    fusionEngine.integrateMemory(cognitiveMemory);
    
    std::cout << "  Integration Memory: " << cognitiveMemory->getId() << std::endl;
    std::cout << "  Integration Task: " << integrationTask->getName() << std::endl;
    std::cout << "  Task Options: " << integrationTask->getOptions().data.size() << " parameters" << std::endl;
    std::cout << "  Memory Store: " << fusionEngine.retrieveRelevantMemories("integration", 10).size() << " memories" << std::endl;
    
    std::cout << std::endl;
    std::cout << "=== Demo Complete ===" << std::endl;
    std::cout << "All cognitive primitives working together successfully!" << std::endl;
    
    return 0;
}