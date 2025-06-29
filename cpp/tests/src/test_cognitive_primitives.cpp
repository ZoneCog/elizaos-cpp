#include <gtest/gtest.h>
#include "elizaos/core.hpp"
#include <memory>
#include <thread>
#include <chrono>

using namespace elizaos;

class CognitivePrimitivesTest : public ::testing::Test {
protected:
    void SetUp() override {
        config_ = AgentConfig{
            "test-agent-id",
            "TestAgent", 
            "A test agent for cognitive primitives testing",
            "Created for testing core cognitive functionality",
            "intelligent"
        };
    }
    
    AgentConfig config_;
};

// ============================================================================
// Enhanced Memory Tests
// ============================================================================

TEST_F(CognitivePrimitivesTest, EnhancedMemoryCreation) {
    MessageMetadata metadata;
    metadata.source = "test_suite";
    metadata.scope = MemoryScope::PRIVATE;
    metadata.tags = {"test", "memory"};
    
    auto memory = std::make_shared<Memory>(
        "enhanced-msg-1",
        "Enhanced memory test content",
        "entity-1", 
        config_.agentId,
        metadata
    );
    
    EXPECT_EQ(memory->getId(), "enhanced-msg-1");
    EXPECT_EQ(memory->getContent(), "Enhanced memory test content");
    EXPECT_EQ(memory->getEntityId(), "entity-1");
    EXPECT_EQ(memory->getAgentId(), config_.agentId);
    EXPECT_FALSE(memory->isUnique());
    EXPECT_EQ(memory->getSimilarity(), 0.0);
}

TEST_F(CognitivePrimitivesTest, MemoryEmbeddingSupport) {
    auto memory = std::make_shared<Memory>(
        "embedded-msg-1",
        "Memory with embedding",
        "entity-1", 
        config_.agentId
    );
    
    // Test embedding functionality
    EmbeddingVector embedding = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f};
    memory->setEmbedding(embedding);
    
    ASSERT_TRUE(memory->getEmbedding().has_value());
    auto retrievedEmbedding = memory->getEmbedding().value();
    EXPECT_EQ(retrievedEmbedding.size(), 5);
    EXPECT_FLOAT_EQ(retrievedEmbedding[0], 0.1f);
    EXPECT_FLOAT_EQ(retrievedEmbedding[4], 0.5f);
}

TEST_F(CognitivePrimitivesTest, MemoryHypergraphConnections) {
    auto memory = std::make_shared<Memory>(
        "hypergraph-msg-1",
        "Memory with hypergraph connections",
        "entity-1", 
        config_.agentId
    );
    
    // Add hypergraph connections
    memory->addHypergraphNode("node-1");
    memory->addHypergraphNode("node-2");
    memory->addHypergraphEdge("edge-1");
    
    auto nodes = memory->getHypergraphNodes();
    auto edges = memory->getHypergraphEdges();
    
    EXPECT_EQ(nodes.size(), 2);
    EXPECT_EQ(edges.size(), 1);
    EXPECT_EQ(nodes[0], "node-1");
    EXPECT_EQ(nodes[1], "node-2");
    EXPECT_EQ(edges[0], "edge-1");
}

// ============================================================================
// Hypergraph Structure Tests
// ============================================================================

TEST_F(CognitivePrimitivesTest, HypergraphNodeCreation) {
    HypergraphNode node("node-1", "ConceptNode");
    
    EXPECT_EQ(node.getId(), "node-1");
    EXPECT_EQ(node.getLabel(), "ConceptNode");
    
    // Test attributes
    node.setAttribute("type", "abstract");
    node.setAttribute("confidence", "0.8");
    
    auto typeAttr = node.getAttribute("type");
    ASSERT_TRUE(typeAttr.has_value());
    EXPECT_EQ(typeAttr.value(), "abstract");
    
    auto nonExistentAttr = node.getAttribute("nonexistent");
    EXPECT_FALSE(nonExistentAttr.has_value());
}

TEST_F(CognitivePrimitivesTest, HypergraphEdgeCreation) {
    std::vector<UUID> nodeIds = {"node-1", "node-2", "node-3"};
    HypergraphEdge edge("edge-1", "RelationEdge", nodeIds);
    
    EXPECT_EQ(edge.getId(), "edge-1");
    EXPECT_EQ(edge.getLabel(), "RelationEdge");
    EXPECT_EQ(edge.getNodeIds().size(), 3);
    EXPECT_EQ(edge.getWeight(), 1.0);
    
    edge.setWeight(0.7);
    EXPECT_DOUBLE_EQ(edge.getWeight(), 0.7);
}

// ============================================================================
// Task Orchestration Tests
// ============================================================================

TEST_F(CognitivePrimitivesTest, TaskCreation) {
    Task task("task-1", "TestTask", "A test task for validation");
    
    EXPECT_EQ(task.getId(), "task-1");
    EXPECT_EQ(task.getName(), "TestTask");
    EXPECT_EQ(task.getDescription(), "A test task for validation");
    EXPECT_EQ(task.getStatus(), TaskStatus::PENDING);
    EXPECT_EQ(task.getPriority(), 0);
}

TEST_F(CognitivePrimitivesTest, TaskTagsAndOptions) {
    Task task("task-2", "TaggedTask", "Task with tags and options");
    
    // Test tags
    task.addTag("queue");
    task.addTag("immediate");
    task.addTag("test");
    
    auto tags = task.getTags();
    EXPECT_EQ(tags.size(), 3);
    EXPECT_EQ(tags[0], "queue");
    EXPECT_EQ(tags[2], "test");
    
    // Test options
    TaskOptions options;
    options.data["param1"] = "value1";
    options.data["param2"] = "value2";
    task.setOptions(options);
    
    auto retrievedOptions = task.getOptions();
    EXPECT_EQ(retrievedOptions.data.size(), 2);
    EXPECT_EQ(retrievedOptions.data.at("param1"), "value1");
}

TEST_F(CognitivePrimitivesTest, TaskScheduling) {
    Task task("task-3", "ScheduledTask", "Task with scheduling");
    
    auto futureTime = std::chrono::system_clock::now() + std::chrono::hours(1);
    task.setScheduledTime(futureTime);
    
    auto scheduledTime = task.getScheduledTime();
    ASSERT_TRUE(scheduledTime.has_value());
    EXPECT_EQ(scheduledTime.value(), futureTime);
    
    task.setPriority(10);
    EXPECT_EQ(task.getPriority(), 10);
}

class TestTaskWorker : public TaskWorker {
public:
    std::string getName() const override {
        return "TestWorker";
    }
    
    bool validate(const Task& task, const State& state, std::shared_ptr<Memory> message) const override {
        (void)task; (void)state; (void)message;
        return true;
    }
    
    bool execute(Task& task, State& state, const TaskOptions& options) override {
        (void)state; (void)options;
        executed = true;
        executedTaskId = task.getId();
        return true;
    }
    
    bool executed = false;
    std::string executedTaskId;
};

TEST_F(CognitivePrimitivesTest, TaskManagerBasicOperations) {
    TaskManager manager;
    
    // Test task creation
    UUID taskId = manager.createTask("TestTask", "Basic task test");
    EXPECT_FALSE(taskId.empty());
    
    // Test task retrieval
    auto task = manager.getTask(taskId);
    ASSERT_NE(task, nullptr);
    EXPECT_EQ(task->getName(), "TestTask");
    
    // Test task scheduling
    auto futureTime = std::chrono::system_clock::now() + std::chrono::minutes(1);
    bool scheduled = manager.scheduleTask(taskId, futureTime);
    EXPECT_TRUE(scheduled);
    
    // Test task cancellation
    bool cancelled = manager.cancelTask(taskId);
    EXPECT_TRUE(cancelled);
    EXPECT_EQ(task->getStatus(), TaskStatus::CANCELLED);
}

TEST_F(CognitivePrimitivesTest, TaskManagerWorkerRegistration) {
    TaskManager manager;
    auto worker = std::make_shared<TestTaskWorker>();
    
    // Register worker
    manager.registerWorker(worker);
    
    // Create a task with matching worker name
    UUID taskId = manager.createTask("TestWorker", "Worker execution test");
    auto task = manager.getTask(taskId);
    task->addTag("queue"); // Required for processing
    
    // Test worker unregistration
    manager.unregisterWorker("TestWorker");
    
    // Should be safe to unregister non-existent worker
    manager.unregisterWorker("NonExistentWorker");
}

// ============================================================================
// Cognitive Fusion Engine Tests
// ============================================================================

class MockSymbolicReasoner : public SymbolicReasoner {
public:
    std::string getName() const override {
        return "MockSymbolic";
    }
    
    std::vector<std::string> reason(const State& state, const std::string& query) override {
        (void)state;
        return {"symbolic_result_" + query};
    }
    
    bool validateRule(const std::string& rule) const override {
        return !rule.empty();
    }
    
    void addRule(const std::string& rule) override {
        rules.push_back(rule);
    }
    
    std::vector<std::string> rules;
};

class MockConnectionistProcessor : public ConnectionistProcessor {
public:
    std::string getName() const override {
        return "MockConnectionist";
    }
    
    EmbeddingVector generateEmbedding(const std::string& input) override {
        // Simple mock embedding based on string length
        float length = static_cast<float>(input.length());
        return {length / 10.0f, length / 20.0f, length / 30.0f};
    }
    
    double computeSimilarity(const EmbeddingVector& a, const EmbeddingVector& b) override {
        if (a.size() != b.size()) return 0.0;
        
        double similarity = 0.0;
        for (size_t i = 0; i < a.size(); ++i) {
            similarity += a[i] * b[i];
        }
        return similarity;
    }
    
    std::vector<std::string> generateResponse(const EmbeddingVector& context) override {
        (void)context;
        return {"connectionist_response"};
    }
};

class MockPatternMatcher : public PatternMatcher {
public:
    std::string getName() const override {
        return "MockPattern";
    }
    
    double matchPattern(const std::string& input, const std::string& pattern) override {
        return (input.find(pattern) != std::string::npos) ? 1.0 : 0.0;
    }
    
    std::vector<std::string> extractPatterns(const std::string& input) override {
        std::vector<std::string> patterns;
        if (input.find("test") != std::string::npos) {
            patterns.push_back("test_pattern");
        }
        return patterns;
    }
};

TEST_F(CognitivePrimitivesTest, CognitiveFusionEngineComponentRegistration) {
    CognitiveFusionEngine engine;
    
    auto symbolicReasoner = std::make_shared<MockSymbolicReasoner>();
    auto connectionistProcessor = std::make_shared<MockConnectionistProcessor>();
    auto patternMatcher = std::make_shared<MockPatternMatcher>();
    
    // Test component registration
    engine.registerSymbolicReasoner(symbolicReasoner);
    engine.registerConnectionistProcessor(connectionistProcessor);
    engine.registerPatternMatcher(patternMatcher);
    
    // Should not throw or crash
    SUCCEED();
}

TEST_F(CognitivePrimitivesTest, CognitiveFusionEngineQueryProcessing) {
    CognitiveFusionEngine engine;
    State state(config_);
    
    auto symbolicReasoner = std::make_shared<MockSymbolicReasoner>();
    auto connectionistProcessor = std::make_shared<MockConnectionistProcessor>();
    
    engine.registerSymbolicReasoner(symbolicReasoner);
    engine.registerConnectionistProcessor(connectionistProcessor);
    
    // Process a query
    auto result = engine.processQuery(state, "test_query");
    
    EXPECT_EQ(result.symbolicResults.size(), 1);
    EXPECT_EQ(result.connectionistResults.size(), 1);
    EXPECT_EQ(result.symbolicResults[0], "symbolic_result_test_query");
    EXPECT_EQ(result.connectionistResults[0], "connectionist_response");
    EXPECT_GT(result.confidence, 0.0);
    EXPECT_LE(result.confidence, 1.0);
}

TEST_F(CognitivePrimitivesTest, CognitiveFusionEngineMemoryIntegration) {
    CognitiveFusionEngine engine;
    
    // Create and integrate memories
    auto memory1 = std::make_shared<Memory>("mem-1", "test content for search", "entity-1", config_.agentId);
    auto memory2 = std::make_shared<Memory>("mem-2", "another memory item", "entity-1", config_.agentId);
    auto memory3 = std::make_shared<Memory>("mem-3", "test related content", "entity-1", config_.agentId);
    
    engine.integrateMemory(memory1);
    engine.integrateMemory(memory2);
    engine.integrateMemory(memory3);
    
    // Retrieve relevant memories
    auto relevantMemories = engine.retrieveRelevantMemories("test", 5);
    
    EXPECT_EQ(relevantMemories.size(), 2); // memory1 and memory3 contain "test"
    EXPECT_EQ(relevantMemories[0]->getId(), "mem-1");
    EXPECT_EQ(relevantMemories[1]->getId(), "mem-3");
}

// ============================================================================
// Integration Tests
// ============================================================================

TEST_F(CognitivePrimitivesTest, MemoryTaskIntegration) {
    // Test integration between enhanced memory and task systems
    TaskManager manager;
    
    // Create a memory-related task
    UUID taskId = manager.createTask("MemoryProcessor", "Process memory content");
    auto task = manager.getTask(taskId);
    
    // Add memory-related options
    TaskOptions options;
    options.data["memory_id"] = "mem-1";
    options.data["operation"] = "analyze";
    task->setOptions(options);
    
    // Create associated memory
    auto memory = std::make_shared<Memory>("mem-1", "Task processing content", "entity-1", config_.agentId);
    EmbeddingVector embedding = {0.1f, 0.2f, 0.3f};
    memory->setEmbedding(embedding);
    
    EXPECT_EQ(task->getOptions().data.at("memory_id"), "mem-1");
    EXPECT_TRUE(memory->getEmbedding().has_value());
}

TEST_F(CognitivePrimitivesTest, HypergraphMemoryTaskFusion) {
    // Test complex integration of all systems
    CognitiveFusionEngine engine;
    TaskManager manager;
    
    // Create hypergraph structures
    HypergraphNode conceptNode("concept-1", "TestConcept");
    conceptNode.setAttribute("importance", "high");
    
    std::vector<UUID> nodeIds = {"concept-1", "concept-2"};
    HypergraphEdge relationEdge("relation-1", "IsRelatedTo", nodeIds);
    relationEdge.setWeight(0.8);
    
    // Create enhanced memory with hypergraph connections
    auto memory = std::make_shared<Memory>("complex-mem-1", "Complex integrated content", "entity-1", config_.agentId);
    memory->addHypergraphNode("concept-1");
    memory->addHypergraphEdge("relation-1");
    
    EmbeddingVector embedding = {0.5f, 0.7f, 0.3f, 0.9f};
    memory->setEmbedding(embedding);
    
    // Integrate with fusion engine
    engine.integrateMemory(memory);
    
    // Create related task
    UUID taskId = manager.createTask("CognitiveFusion", "Perform cognitive fusion analysis");
    auto task = manager.getTask(taskId);
    task->addTag("fusion");
    task->addTag("analysis");
    
    // Verify integration
    EXPECT_EQ(memory->getHypergraphNodes().size(), 1);
    EXPECT_EQ(memory->getHypergraphEdges().size(), 1);
    EXPECT_TRUE(memory->getEmbedding().has_value());
    EXPECT_EQ(task->getTags().size(), 2);
    
    auto relevantMemories = engine.retrieveRelevantMemories("content", 1);
    EXPECT_EQ(relevantMemories.size(), 1);
    EXPECT_EQ(relevantMemories[0]->getId(), "complex-mem-1");
}