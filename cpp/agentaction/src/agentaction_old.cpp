#include "elizaos/agentaction.hpp"
#include <algorithm>
#include <sstream>

namespace elizaos {

AgentAction::AgentAction() {
    memory_ = std::make_shared<AgentMemoryManager>();
    logger_ = std::make_shared<AgentLogger>();
}

AgentAction::~AgentAction() = default;

void AgentAction::addAction(const std::string& name, const ManagedAction& action) {
    actions_[name] = std::make_shared<ManagedAction>(action);
    
    // Create memory entry for action
    std::unordered_map<std::string, std::string> metadata;
    metadata["name"] = name;
    metadata["description"] = action.description;
    
    // Create a simple Memory object for action storage
    auto memory = std::make_shared<Memory>();
    memory->content = action.name + " - " + action.description;
    memory->metadata = metadata;
    
    memory_->createMemory(memory, "actions");
}

JsonValue AgentAction::useAction(const std::string& function_name, const JsonValue& arguments) {
    JsonValue result;
    
    auto it = actions_.find(function_name);
    if (it == actions_.end()) {
        addToActionHistory(function_name, arguments, false);
        logger_->log("Warning: action was hallucinated: " + function_name, "warning");
        
        result["success"] = false;
        result["error"] = std::string("Action not found");
        return result;
    }
    
    addToActionHistory(function_name, arguments, true);
    
    try {
        auto action = it->second;
        if (action->handler) {
            result = action->handler(arguments);
            result["success"] = true;
        } else {
            result["success"] = false;
            result["error"] = std::string("No handler for action");
        }
    } catch (const std::exception& e) {
        result["success"] = false;
        result["error"] = std::string("Exception: ") + e.what();
        addToActionHistory(function_name, arguments, false);
    }
    
    return result;
}

std::vector<JsonValue> AgentAction::searchActions(const std::string& search_text, int n_results) {
    auto memories = memory_->searchMemory("actions", search_text, n_results);
    std::vector<JsonValue> results;
    
    for (const auto& memory : memories) {
        JsonValue action_data;
        action_data["document"] = memory.content;
        action_data["metadata"] = JsonValue{};
        
        // Convert Memory metadata to JsonValue
        JsonValue metadata_map;
        for (const auto& pair : memory.metadata) {
            metadata_map[pair.first] = pair.second;
        }
        action_data["metadata"] = metadata_map;
        
        results.push_back(action_data);
    }
    
    return results;
}

std::vector<JsonValue> AgentAction::getAvailableActions(const std::string& search_text, int n_results) {
    auto available_actions = searchActions(search_text, n_results);
    std::vector<JsonValue> recommended_actions;
    std::vector<JsonValue> ignored_actions;
    
    auto last_action = getLastAction();
    
    if (!last_action.empty()) {
        // Get the last action name
        std::string last_action_name;
        if (last_action.count("name")) {
            try {
                last_action_name = std::any_cast<std::string>(last_action["name"]);
            } catch (const std::bad_any_cast& e) {
                // Handle conversion error
                logger_->log("Error converting last action name: " + std::string(e.what()), "error");
            }
        }
        
        if (!last_action_name.empty() && actions_.count(last_action_name)) {
            auto action = actions_[last_action_name];
            
            // Get recommended actions
            for (const auto& recommended : action->suggestion_after_actions) {
                auto action_from_memory = getActionFromMemory(recommended);
                if (!action_from_memory.empty()) {
                    action_from_memory["recommended"] = true;
                    recommended_actions.push_back(action_from_memory);
                }
            }
            
            // Get ignored actions
            for (const auto& ignored : action->never_after_actions) {
                auto action_from_memory = getActionFromMemory(ignored);
                if (!action_from_memory.empty()) {
                    ignored_actions.push_back(action_from_memory);
                }
            }
        }
    }
    
    // Add recommended actions that aren't already in available_actions
    for (const auto& recommended : recommended_actions) {
        bool found = false;
        for (const auto& available : available_actions) {
            if (available == recommended) {
                found = true;
                break;
            }
        }
        if (!found) {
            available_actions.push_back(recommended);
        }
    }
    
    // Remove ignored actions
    for (const auto& ignored : ignored_actions) {
        available_actions.erase(
            std::remove_if(available_actions.begin(), available_actions.end(),
                          [&ignored](const JsonValue& action) { return action == ignored; }),
            available_actions.end()
        );
    }
    
    return available_actions;
}

std::shared_ptr<Action> AgentAction::getAction(const std::string& name) {
    auto it = actions_.find(name);
    if (it != actions_.end()) {
        return it->second;
    }
    return nullptr;
}

bool AgentAction::removeAction(const std::string& name) {
    auto it = actions_.find(name);
    if (it != actions_.end()) {
        actions_.erase(it);
        memory_->deleteMemory("actions", name);
        return true;
    }
    return false;
}

const std::unordered_map<std::string, std::shared_ptr<Action>>& AgentAction::getActions() const {
    return actions_;
}

void AgentAction::addToActionHistory(const std::string& action_name, const JsonValue& arguments, bool success) {
    JsonValue metadata;
    metadata["success"] = success;
    
    // Copy arguments to metadata
    for (const auto& arg : arguments) {
        metadata[arg.first] = arg.second;
    }
    
    memory_->createMemory("action_history", action_name, metadata);
}

std::vector<JsonValue> AgentAction::getActionHistory(int n_results) {
    auto memories = memory_->getMemories("action_history", n_results);
    std::vector<JsonValue> results;
    
    for (const auto& memory : memories) {
        JsonValue action_data;
        action_data["document"] = memory.content;
        
        // Convert Memory metadata to JsonValue
        JsonValue metadata_map;
        for (const auto& pair : memory.metadata) {
            metadata_map[pair.first] = pair.second;
        }
        action_data["metadata"] = metadata_map;
        
        results.push_back(action_data);
    }
    
    return results;
}

JsonValue AgentAction::getLastAction() {
    auto history = getActionHistory(1);
    if (history.empty()) {
        return JsonValue{};
    }
    return history[0];
}

void AgentAction::clearActions() {
    actions_.clear();
    memory_->wipeCategory("actions");
}

std::string AgentAction::composeActionPrompt(const Action& action, const JsonValue& values) {
    std::string prompt = action.prompt;
    
    if (action.builder) {
        prompt = action.builder(values);
    }
    
    return prompt;
}

JsonValue AgentAction::getFormattedActions(const std::string& search_text) {
    JsonValue result;
    
    auto available_actions = getAvailableActions(search_text, 5);
    
    // Sort actions so recommended ones come first
    std::sort(available_actions.begin(), available_actions.end(),
              [](const JsonValue& a, const JsonValue& b) {
                  bool a_recommended = false, b_recommended = false;
                  
                  if (a.count("recommended")) {
                      try {
                          a_recommended = std::any_cast<bool>(a.at("recommended"));
                      } catch (const std::bad_any_cast&) {}
                  }
                  
                  if (b.count("recommended")) {
                      try {
                          b_recommended = std::any_cast<bool>(b.at("recommended"));
                      } catch (const std::bad_any_cast&) {}
                  }
                  
                  return a_recommended > b_recommended;
              });
    
    // Create formatted actions string
    std::stringstream formatted_actions;
    formatted_actions << "Available actions for me to choose from:\n";
    
    for (const auto& action : available_actions) {
        bool is_recommended = false;
        if (action.count("recommended")) {
            try {
                is_recommended = std::any_cast<bool>(action.at("recommended"));
            } catch (const std::bad_any_cast&) {}
        }
        
        std::string document;
        if (action.count("document")) {
            try {
                document = std::any_cast<std::string>(action.at("document"));
            } catch (const std::bad_any_cast&) {}
        }
        
        if (is_recommended) {
            formatted_actions << "(recommended) " << document << "\n";
        } else {
            formatted_actions << document << "\n";
        }
    }
    
    // Create short actions string
    std::stringstream short_actions;
    short_actions << "Available actions (name): ";
    
    for (size_t i = 0; i < available_actions.size(); ++i) {
        if (i > 0) short_actions << ", ";
        
        std::string name;
        if (available_actions[i].count("metadata")) {
            try {
                auto metadata = std::any_cast<JsonValue>(available_actions[i].at("metadata"));
                if (metadata.count("name")) {
                    name = std::any_cast<std::string>(metadata.at("name"));
                }
            } catch (const std::bad_any_cast&) {}
        }
        
        short_actions << name;
    }
    
    result["available_actions"] = available_actions;
    result["formatted_actions"] = formatted_actions.str();
    result["short_actions"] = short_actions.str();
    
    return result;
}

JsonValue AgentAction::getActionFromMemory(const std::string& action_name) {
    std::unordered_map<std::string, std::string> filter_metadata;
    filter_metadata["name"] = action_name;
    
    auto memories = memory_->getMemories("actions", 1, filter_metadata);
    
    if (memories.empty()) {
        return JsonValue{};
    }
    
    JsonValue action_data;
    action_data["document"] = memories[0].content;
    
    // Convert Memory metadata to JsonValue
    JsonValue metadata_map;
    for (const auto& pair : memories[0].metadata) {
        metadata_map[pair.first] = pair.second;
    }
    action_data["metadata"] = metadata_map;
    
    return action_data;
}

} // namespace elizaos