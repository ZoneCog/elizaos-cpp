#include "elizaos/core.hpp"
#include <random>
#include <sstream>
#include <iomanip>

namespace elizaos {

// Utility function to generate UUIDs (simplified version)
std::string generateUUID() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);
    
    std::stringstream ss;
    int i;
    ss << std::hex;
    for (i = 0; i < 8; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 4; i++) {
        ss << dis(gen);
    }
    ss << "-4";
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    ss << dis2(gen);
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 12; i++) {
        ss << dis(gen);
    }
    return ss.str();
}

// Memory implementation
Memory::Memory(const UUID& id, const std::string& content, const UUID& userId, const UUID& agentId)
    : id_(id), content_(content), userId_(userId), agentId_(agentId), 
      createdAt_(std::chrono::system_clock::now()) {
}

// State implementation  
State::State(const AgentConfig& config) : config_(config) {
}

void State::addActor(const Actor& actor) {
    actors_.push_back(actor);
}

void State::addGoal(const Goal& goal) {
    goals_.push_back(goal);
}

void State::addRecentMessage(std::shared_ptr<Memory> memory) {
    recentMessages_.push_back(memory);
    
    // Keep only recent messages (e.g., last 32)
    const size_t maxRecentMessages = 32;
    if (recentMessages_.size() > maxRecentMessages) {
        recentMessages_.erase(recentMessages_.begin(), 
                            recentMessages_.begin() + (recentMessages_.size() - maxRecentMessages));
    }
}

} // namespace elizaos