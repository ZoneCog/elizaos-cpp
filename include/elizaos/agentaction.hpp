#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include <any>
#include "elizaos/core.hpp"
#include "elizaos/agentmemory.hpp"
#include "elizaos/agentlogger.hpp"

namespace elizaos {

/**
 * @brief Simple JSON-like container using std::any
 */
using JsonValue = std::unordered_map<std::string, std::any>;

/**
 * @brief Represents a function that can be executed as an action
 */
using ActionHandler = std::function<JsonValue(const JsonValue&)>;

/**
 * @brief Represents a function that builds action prompts
 */
using ActionBuilder = std::function<std::string(const JsonValue&)>;

/**
 * @brief Represents a manageable action that can be executed by an agent
 * This is different from the core Action interface - it's for action management
 */
struct ManagedAction {
    std::string name;
    std::string prompt;
    std::string description;
    ActionBuilder builder;
    ActionHandler handler;
    std::vector<std::string> suggestion_after_actions;
    std::vector<std::string> never_after_actions;
    JsonValue function_definition;
    
    ManagedAction() = default;
    
    ManagedAction(const std::string& n, const std::string& p, const std::string& d, 
           ActionHandler h, const JsonValue& func_def)
        : name(n), prompt(p), description(d), handler(h), function_definition(func_def) {}
};

/**
 * @brief Action management system for orchestrating agent actions
 */
class AgentAction {
public:
    AgentAction();
    ~AgentAction();
    
    /**
     * @brief Add an action to the system
     * @param name The name of the action
     * @param action The action to add
     */
    void addAction(const std::string& name, const ManagedAction& action);
    
    /**
     * @brief Execute an action by name
     * @param function_name The name of the function to execute
     * @param arguments JSON arguments for the function
     * @return JSON result containing success status and output
     */
    JsonValue useAction(const std::string& function_name, const JsonValue& arguments);
    
    /**
     * @brief Search for actions based on query text
     * @param search_text The text to search for
     * @param n_results Maximum number of results to return
     * @return Vector of actions matching the search
     */
    std::vector<JsonValue> searchActions(const std::string& search_text, int n_results = 5);
    
    /**
     * @brief Get available actions based on context and last action
     * @param search_text The search query
     * @param n_results Maximum number of results
     * @return Vector of available actions
     */
    std::vector<JsonValue> getAvailableActions(const std::string& search_text, int n_results = 5);
    
    /**
     * @brief Get an action by name
     * @param name The name of the action
     * @return Pointer to action or nullptr if not found
     */
    std::shared_ptr<ManagedAction> getAction(const std::string& name);
    
    /**
     * @brief Remove an action by name
     * @param name The name of the action to remove
     * @return True if action was removed, false if not found
     */
    bool removeAction(const std::string& name);
    
    /**
     * @brief Get all actions
     * @return Map of all actions
     */
    const std::unordered_map<std::string, std::shared_ptr<ManagedAction>>& getActions() const;
    
    /**
     * @brief Add an action to the execution history
     * @param action_name The name of the action
     * @param arguments The arguments used
     * @param success Whether the action was successful
     */
    void addToActionHistory(const std::string& action_name, const JsonValue& arguments, bool success = true);
    
    /**
     * @brief Get recent action history
     * @param n_results Maximum number of results
     * @return Vector of recent actions
     */
    std::vector<JsonValue> getActionHistory(int n_results = 20);
    
    /**
     * @brief Get the last executed action
     * @return JSON of last action or null if none
     */
    JsonValue getLastAction();
    
    /**
     * @brief Clear all actions
     */
    void clearActions();
    
    /**
     * @brief Compose an action prompt
     * @param action The action to compose prompt for
     * @param values Values to insert into the prompt
     * @return Composed prompt string
     */
    std::string composeActionPrompt(const ManagedAction& action, const JsonValue& values);
    
    /**
     * @brief Get formatted actions for display
     * @param search_text Search query
     * @return JSON object with formatted action lists
     */
    JsonValue getFormattedActions(const std::string& search_text);

private:
    std::unordered_map<std::string, std::shared_ptr<ManagedAction>> actions_;
    std::shared_ptr<AgentMemoryManager> memory_;
    std::shared_ptr<AgentLogger> logger_;
    
    /**
     * @brief Get action from memory by name
     * @param action_name The name of the action
     * @return JSON representation of the action or null
     */
    JsonValue getActionFromMemory(const std::string& action_name);
};

} // namespace elizaos