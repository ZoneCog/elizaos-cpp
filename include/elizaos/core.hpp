#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <functional>
#include <thread>
#include <atomic>
#include <chrono>

namespace elizaos {

// Forward declarations
class Agent;
class Memory;
class Action;
class State;

// Basic types
using UUID = std::string;
using Timestamp = std::chrono::system_clock::time_point;

/**
 * Core data structures representing agent entities and state
 * Based on the TypeScript State interface from eliza/packages/core
 */
struct AgentConfig {
    UUID agentId;
    std::string agentName;
    std::string bio;
    std::string lore;
    std::string adjective;
};

struct Actor {
    UUID id;
    std::string name;
    std::string details;
};

struct Goal {
    UUID id;
    std::string description;
    std::string status;
    Timestamp createdAt;
    Timestamp updatedAt;
};

/**
 * Memory represents a single message or interaction in the system
 * Corresponds to the Memory interface in the TypeScript implementation
 */
class Memory {
public:
    Memory(const UUID& id, const std::string& content, const UUID& userId, const UUID& agentId);
    
    const UUID& getId() const { return id_; }
    const std::string& getContent() const { return content_; }
    const UUID& getUserId() const { return userId_; }
    const UUID& getAgentId() const { return agentId_; }
    Timestamp getCreatedAt() const { return createdAt_; }
    
private:
    UUID id_;
    std::string content_;
    UUID userId_;
    UUID agentId_;
    Timestamp createdAt_;
};

/**
 * State represents the complete context for agent decision making
 * Based on the State interface from the TypeScript implementation
 */
class State {
public:
    State(const AgentConfig& config);
    
    // Agent identity
    const UUID& getAgentId() const { return config_.agentId; }
    const std::string& getAgentName() const { return config_.agentName; }
    const std::string& getBio() const { return config_.bio; }
    const std::string& getLore() const { return config_.lore; }
    
    // Context management
    void addActor(const Actor& actor);
    void addGoal(const Goal& goal);
    void addRecentMessage(std::shared_ptr<Memory> memory);
    
    const std::vector<Actor>& getActors() const { return actors_; }
    const std::vector<Goal>& getGoals() const { return goals_; }
    const std::vector<std::shared_ptr<Memory>>& getRecentMessages() const { return recentMessages_; }
    
private:
    AgentConfig config_;
    std::vector<Actor> actors_;
    std::vector<Goal> goals_;
    std::vector<std::shared_ptr<Memory>> recentMessages_;
};

/**
 * Action interface for agent behaviors
 * Corresponds to the Action system in the TypeScript implementation
 */
class Action {
public:
    virtual ~Action() = default;
    virtual std::string getName() const = 0;
    virtual bool validate(const State& state, std::shared_ptr<Memory> message) const = 0;
    virtual bool execute(State& state, std::shared_ptr<Memory> message) = 0;
};

/**
 * Provider interface for state composition
 * Corresponds to the Provider interface in the TypeScript implementation
 */
class Provider {
public:
    virtual ~Provider() = default;
    virtual std::string getName() const = 0;
    virtual std::unordered_map<std::string, std::string> get(const State& state, std::shared_ptr<Memory> message) = 0;
};

} // namespace elizaos