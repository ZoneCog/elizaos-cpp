#include <gtest/gtest.h>
#include "elizaos/core.hpp"
#include <memory>

using namespace elizaos;

class CoreTest : public ::testing::Test {
protected:
    void SetUp() override {
        config_ = AgentConfig{
            "test-agent-id",
            "TestAgent", 
            "A test agent for unit testing",
            "Created for testing purposes",
            "helpful"
        };
    }
    
    AgentConfig config_;
};

TEST_F(CoreTest, MemoryCreation) {
    auto memory = std::make_shared<Memory>(
        "msg-1",
        "Hello, world!",
        "user-1", 
        config_.agentId
    );
    
    EXPECT_EQ(memory->getId(), "msg-1");
    EXPECT_EQ(memory->getContent(), "Hello, world!");
    EXPECT_EQ(memory->getEntityId(), "user-1");
    EXPECT_EQ(memory->getAgentId(), config_.agentId);
}

TEST_F(CoreTest, StateCreation) {
    State state(config_);
    
    EXPECT_EQ(state.getAgentId(), config_.agentId);
    EXPECT_EQ(state.getAgentName(), config_.agentName);
    EXPECT_EQ(state.getBio(), config_.bio);
    EXPECT_EQ(state.getLore(), config_.lore);
}

TEST_F(CoreTest, StateActorManagement) {
    State state(config_);
    
    Actor actor1{"actor-1", "Alice", "A helpful user"};
    Actor actor2{"actor-2", "Bob", "Another user"};
    
    state.addActor(actor1);
    state.addActor(actor2);
    
    const auto& actors = state.getActors();
    EXPECT_EQ(actors.size(), 2);
    EXPECT_EQ(actors[0].name, "Alice");
    EXPECT_EQ(actors[1].name, "Bob");
}

TEST_F(CoreTest, StateGoalManagement) {
    State state(config_);
    
    Goal goal1{"goal-1", "Complete task A", "active", 
               std::chrono::system_clock::now(), std::chrono::system_clock::now()};
    Goal goal2{"goal-2", "Complete task B", "pending",
               std::chrono::system_clock::now(), std::chrono::system_clock::now()};
    
    state.addGoal(goal1);
    state.addGoal(goal2);
    
    const auto& goals = state.getGoals();
    EXPECT_EQ(goals.size(), 2);
    EXPECT_EQ(goals[0].description, "Complete task A");
    EXPECT_EQ(goals[1].description, "Complete task B");
}

TEST_F(CoreTest, StateRecentMessagesManagement) {
    State state(config_);
    
    auto memory1 = std::make_shared<Memory>("msg-1", "First message", "user-1", config_.agentId);
    auto memory2 = std::make_shared<Memory>("msg-2", "Second message", "user-1", config_.agentId);
    
    state.addRecentMessage(memory1);
    state.addRecentMessage(memory2);
    
    const auto& messages = state.getRecentMessages();
    EXPECT_EQ(messages.size(), 2);
    EXPECT_EQ(messages[0]->getContent(), "First message");
    EXPECT_EQ(messages[1]->getContent(), "Second message");
}

TEST_F(CoreTest, StateRecentMessagesLimit) {
    State state(config_);
    
    // Add more than the limit (32) to test truncation
    for (int i = 0; i < 35; ++i) {
        auto memory = std::make_shared<Memory>(
            "msg-" + std::to_string(i), 
            "Message " + std::to_string(i), 
            "user-1", 
            config_.agentId
        );
        state.addRecentMessage(memory);
    }
    
    const auto& messages = state.getRecentMessages();
    EXPECT_EQ(messages.size(), 32); // Should be limited to 32
    EXPECT_EQ(messages[0]->getContent(), "Message 3"); // First 3 should be removed
    EXPECT_EQ(messages[31]->getContent(), "Message 34"); // Last should be message 34
}