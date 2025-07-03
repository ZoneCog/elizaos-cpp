#include "elizaos/agentshell.hpp"
#include "elizaos/agentlogger.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

// Conditional readline support
#ifdef HAVE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

namespace elizaos {

// Global shell instance
std::shared_ptr<AgentShell> globalShell = std::make_shared<AgentShell>();

AgentShell::AgentShell() 
    : running_(false), prompt_("elizaos> "), historyEnabled_(true) {
    initializeBuiltinCommands();
}

AgentShell::~AgentShell() {
    stop();
}

void AgentShell::start(const std::string& prompt) {
    if (running_) {
        return; // Already running
    }
    
    prompt_ = prompt;
    running_ = true;
    
    // Start shell in separate thread
    shellThread_ = std::make_unique<std::thread>(&AgentShell::shellLoop, this);
    
    logInfo("Interactive shell started", "agentshell");
}

void AgentShell::stop() {
    if (!running_) {
        return;
    }
    
    running_ = false;
    
    if (shellThread_ && shellThread_->joinable()) {
        shellThread_->join();
    }
    
    logInfo("Interactive shell stopped", "agentshell");
}

void AgentShell::shellLoop() {
    logSuccess("ElizaOS Interactive Shell", "agentshell");
    logInfo("Type 'help' for available commands, 'exit' to quit", "agentshell");
    
    while (running_) {
        std::string command;
        
#ifdef HAVE_READLINE
        // Use readline for better input handling with history
        char* input = readline(prompt_.c_str());
        
        if (!input) {
            // EOF (Ctrl+D)
            break;
        }
        
        command = std::string(input);
        free(input);
        
        // Add to readline history
        if (!command.empty() && historyEnabled_) {
            add_history(command.c_str());
        }
#else
        // Fallback to basic input
        std::cout << prompt_;
        if (!std::getline(std::cin, command)) {
            // EOF
            break;
        }
#endif
        
        // Skip empty commands
        if (command.empty()) {
            continue;
        }
        
        // Add to internal history
        if (historyEnabled_) {
            std::lock_guard<std::mutex> lock(historyMutex_);
            commandHistory_.push_back(command);
        }
        
        // Execute command
        auto result = executeCommand(command);
        
        // Display result
        if (!result.output.empty()) {
            std::cout << result.output << std::endl;
        }
        
        if (!result.success && !result.error.empty()) {
            logError(result.error, "agentshell");
        }
        
        // Check for exit command
        if (command == "exit" || command == "quit") {
            break;
        }
    }
    
    running_ = false;
}

ShellCommandResult AgentShell::executeCommand(const std::string& command) {
    auto tokens = parseCommand(command);
    
    if (tokens.empty()) {
        return ShellCommandResult(true, "", "", 0);
    }
    
    std::string commandName = tokens[0];
    
    // Look up command handler
    std::lock_guard<std::mutex> lock(commandsMutex_);
    auto it = commandHandlers_.find(commandName);
    
    if (it != commandHandlers_.end()) {
        try {
            return it->second(tokens);
        } catch (const std::exception& e) {
            return ShellCommandResult(false, "", "Command error: " + std::string(e.what()), 1);
        }
    } else {
        return ShellCommandResult(false, "", "Unknown command: " + commandName + " (type 'help' for available commands)", 1);
    }
}

std::vector<std::string> AgentShell::parseCommand(const std::string& command) {
    std::vector<std::string> tokens;
    std::istringstream iss(command);
    std::string token;
    
    // Simple tokenization by whitespace
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

void AgentShell::registerCommand(const std::string& commandName, CommandHandler handler) {
    std::lock_guard<std::mutex> lock(commandsMutex_);
    commandHandlers_[commandName] = handler;
}

void AgentShell::unregisterCommand(const std::string& commandName) {
    std::lock_guard<std::mutex> lock(commandsMutex_);
    commandHandlers_.erase(commandName);
}

std::vector<std::string> AgentShell::getAvailableCommands() const {
    std::lock_guard<std::mutex> lock(commandsMutex_);
    std::vector<std::string> commands;
    
    for (const auto& pair : commandHandlers_) {
        commands.push_back(pair.first);
    }
    
    std::sort(commands.begin(), commands.end());
    return commands;
}

void AgentShell::setPrompt(const std::string& prompt) {
    prompt_ = prompt;
}

void AgentShell::setHistoryEnabled(bool enabled) {
    historyEnabled_ = enabled;
}

const std::vector<std::string>& AgentShell::getHistory() const {
    std::lock_guard<std::mutex> lock(historyMutex_);
    return commandHistory_;
}

void AgentShell::clearHistory() {
    std::lock_guard<std::mutex> lock(historyMutex_);
    commandHistory_.clear();
#ifdef HAVE_READLINE
    clear_history();
#endif
}

void AgentShell::initializeBuiltinCommands() {
    registerCommand("help", [this](const std::vector<std::string>& args) { return helpCommand(args); });
    registerCommand("exit", [this](const std::vector<std::string>& args) { return exitCommand(args); });
    registerCommand("quit", [this](const std::vector<std::string>& args) { return exitCommand(args); });
    registerCommand("history", [this](const std::vector<std::string>& args) { return historyCommand(args); });
    registerCommand("clear", [this](const std::vector<std::string>& args) { return clearCommand(args); });
    registerCommand("echo", [this](const std::vector<std::string>& args) { return echoCommand(args); });
    registerCommand("status", [this](const std::vector<std::string>& args) { return statusCommand(args); });
}

ShellCommandResult AgentShell::helpCommand(const std::vector<std::string>& args) {
    (void)args; // Suppress unused parameter warning
    
    std::stringstream ss;
    ss << "Available commands:\n";
    
    auto commands = getAvailableCommands();
    for (const auto& cmd : commands) {
        ss << "  " << cmd;
        
        // Add descriptions for built-in commands
        if (cmd == "help") ss << " - Show this help message";
        else if (cmd == "exit" || cmd == "quit") ss << " - Exit the shell";
        else if (cmd == "history") ss << " - Show command history";
        else if (cmd == "clear") ss << " - Clear the screen";
        else if (cmd == "echo") ss << " - Echo text to output";
        else if (cmd == "status") ss << " - Show system status";
        
        ss << "\n";
    }
    
    return ShellCommandResult(true, ss.str(), "", 0);
}

ShellCommandResult AgentShell::exitCommand(const std::vector<std::string>& args) {
    (void)args; // Suppress unused parameter warning
    running_ = false;
    return ShellCommandResult(true, "Goodbye!", "", 0);
}

ShellCommandResult AgentShell::historyCommand(const std::vector<std::string>& args) {
    (void)args; // Suppress unused parameter warning
    
    std::lock_guard<std::mutex> lock(historyMutex_);
    
    if (commandHistory_.empty()) {
        return ShellCommandResult(true, "No command history", "", 0);
    }
    
    std::stringstream ss;
    for (size_t i = 0; i < commandHistory_.size(); ++i) {
        ss << "  " << (i + 1) << ": " << commandHistory_[i] << "\n";
    }
    
    return ShellCommandResult(true, ss.str(), "", 0);
}

ShellCommandResult AgentShell::clearCommand(const std::vector<std::string>& args) {
    (void)args; // Suppress unused parameter warning
    
    // Clear screen using ANSI escape codes
    std::cout << "\033[2J\033[H" << std::flush;
    return ShellCommandResult(true, "", "", 0);
}

ShellCommandResult AgentShell::echoCommand(const std::vector<std::string>& args) {
    std::stringstream ss;
    
    for (size_t i = 1; i < args.size(); ++i) {
        if (i > 1) ss << " ";
        ss << args[i];
    }
    
    return ShellCommandResult(true, ss.str(), "", 0);
}

ShellCommandResult AgentShell::statusCommand(const std::vector<std::string>& args) {
    (void)args; // Suppress unused parameter warning
    
    std::stringstream ss;
    ss << "ElizaOS C++ Framework Status:\n";
    ss << "  Shell: Running\n";
    ss << "  Logger: Available\n";
    ss << "  Communications: Available\n";
    ss << "  Memory: Available\n";
    ss << "  Agent Loop: Available\n";
    ss << "  Commands registered: " << getAvailableCommands().size() << "\n";
#ifdef HAVE_READLINE
    ss << "  Input mode: Enhanced (readline)\n";
#else
    ss << "  Input mode: Basic\n";
#endif
    
    return ShellCommandResult(true, ss.str(), "", 0);
}

// Convenience functions
void startInteractiveShell() {
    globalShell->start();
}

void stopInteractiveShell() {
    globalShell->stop();
}

bool executeShellCommand(const std::string& command) {
    auto result = globalShell->executeCommand(command);
    return result.success;
}

void registerShellCommand(const std::string& name, CommandHandler handler) {
    globalShell->registerCommand(name, handler);
}

} // namespace elizaos
