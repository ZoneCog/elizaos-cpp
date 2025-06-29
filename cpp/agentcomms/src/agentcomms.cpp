#include "elizaos/agentcomms.hpp"
#include <chrono>
#include <algorithm>
#include <iostream>
#include <atomic>

namespace elizaos {

// Global communication manager instance
std::shared_ptr<AgentComms> globalComms = std::make_shared<AgentComms>();

// Message implementation
Message::Message(
    const std::string& id,
    MessageType type,
    const std::string& sender,
    const std::string& receiver,
    const std::string& content
) : id(id), type(type), sender(sender), receiver(receiver), content(content),
    timestamp(std::chrono::system_clock::now()) {
    if (this->id.empty()) {
        // Generate unique timestamp-based ID with counter
        static std::atomic<uint64_t> counter{0};
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()).count();
        this->id = "msg_" + std::to_string(timestamp) + "_" + std::to_string(counter++);
    }
}

// CommChannel implementation
CommChannel::CommChannel(const std::string& channelId)
    : channelId_(channelId), active_(false), stopRequested_(false) {
}

CommChannel::~CommChannel() {
    stop();
}

bool CommChannel::sendMessage(const Message& message) {
    std::lock_guard<std::mutex> lock(queueMutex_);
    if (!active_) {
        return false;
    }
    
    messageQueue_.push(message);
    queueCondition_.notify_one();
    return true;
}

void CommChannel::setMessageHandler(MessageHandler handler) {
    messageHandler_ = handler;
}

void CommChannel::start() {
    if (active_) {
        return; // Already active
    }
    
    active_ = true;
    stopRequested_ = false;
    processingThread_ = std::make_unique<std::thread>(&CommChannel::processMessages, this);
}

void CommChannel::stop() {
    if (!active_) {
        return;
    }
    
    stopRequested_ = true;
    queueCondition_.notify_all();
    
    if (processingThread_ && processingThread_->joinable()) {
        processingThread_->join();
    }
    
    active_ = false;
}

void CommChannel::processMessages() {
    while (!stopRequested_) {
        std::unique_lock<std::mutex> lock(queueMutex_);
        
        // Wait for messages or stop signal
        queueCondition_.wait(lock, [this] {
            return !messageQueue_.empty() || stopRequested_;
        });
        
        // Process all available messages
        while (!messageQueue_.empty() && !stopRequested_) {
            Message message = messageQueue_.front();
            messageQueue_.pop();
            
            lock.unlock();
            
            // Call message handler if set
            if (messageHandler_) {
                try {
                    messageHandler_(message);
                } catch (const std::exception& e) {
                    // Log error but continue processing
                    std::cerr << "Error in message handler: " << e.what() << std::endl;
                }
            }
            
            lock.lock();
        }
    }
}

// AgentComms implementation
AgentComms::AgentComms() : started_(false) {
}

AgentComms::~AgentComms() {
    stop();
}

std::shared_ptr<CommChannel> AgentComms::createChannel(const std::string& channelId) {
    std::lock_guard<std::mutex> lock(channelsMutex_);
    
    // Check if channel already exists
    auto it = channels_.find(channelId);
    if (it != channels_.end()) {
        return it->second;
    }
    
    // Create new channel
    auto channel = std::make_shared<CommChannel>(channelId);
    channels_[channelId] = channel;
    
    // Set up global handler forwarding
    if (globalHandler_) {
        channel->setMessageHandler(globalHandler_);
    }
    
    // Start channel if communication system is started
    if (started_) {
        channel->start();
    }
    
    return channel;
}

std::shared_ptr<CommChannel> AgentComms::getChannel(const std::string& channelId) {
    std::lock_guard<std::mutex> lock(channelsMutex_);
    
    auto it = channels_.find(channelId);
    return (it != channels_.end()) ? it->second : nullptr;
}

void AgentComms::removeChannel(const std::string& channelId) {
    std::lock_guard<std::mutex> lock(channelsMutex_);
    
    auto it = channels_.find(channelId);
    if (it != channels_.end()) {
        it->second->stop();
        channels_.erase(it);
    }
}

bool AgentComms::sendMessage(const std::string& channelId, const Message& message) {
    auto channel = getChannel(channelId);
    if (!channel) {
        return false;
    }
    
    return channel->sendMessage(message);
}

void AgentComms::broadcastMessage(const Message& message) {
    std::lock_guard<std::mutex> lock(channelsMutex_);
    
    for (const auto& pair : channels_) {
        pair.second->sendMessage(message);
    }
}

std::vector<std::string> AgentComms::getActiveChannels() const {
    std::lock_guard<std::mutex> lock(channelsMutex_);
    
    std::vector<std::string> activeChannels;
    for (const auto& pair : channels_) {
        if (pair.second->isActive()) {
            activeChannels.push_back(pair.first);
        }
    }
    
    return activeChannels;
}

void AgentComms::setGlobalMessageHandler(MessageHandler handler) {
    std::lock_guard<std::mutex> lock(channelsMutex_);
    globalHandler_ = handler;
    
    // Update all existing channels
    for (const auto& pair : channels_) {
        pair.second->setMessageHandler(handler);
    }
}

void AgentComms::start() {
    if (started_) {
        return;
    }
    
    std::lock_guard<std::mutex> lock(channelsMutex_);
    started_ = true;
    
    // Start all existing channels
    for (const auto& pair : channels_) {
        pair.second->start();
    }
}

void AgentComms::stop() {
    if (!started_) {
        return;
    }
    
    std::lock_guard<std::mutex> lock(channelsMutex_);
    started_ = false;
    
    // Stop all channels
    for (const auto& pair : channels_) {
        pair.second->stop();
    }
}

// TCPConnector implementation (basic framework)
TCPConnector::TCPConnector() : connected_(false) {
}

TCPConnector::~TCPConnector() {
    disconnect();
}

bool TCPConnector::connect(const std::string& connectionString) {
    // Basic implementation - in a full implementation this would
    // parse the connection string and establish a TCP connection
    (void)connectionString; // Suppress unused parameter warning
    connected_ = true;
    return true;
}

void TCPConnector::disconnect() {
    connected_ = false;
}

bool TCPConnector::sendData(const std::string& data) {
    if (!connected_) {
        return false;
    }
    
    // In a full implementation, this would send data over the TCP socket
    // For now, just simulate success
    (void)data; // Suppress unused parameter warning
    return true;
}

void TCPConnector::setDataHandler(std::function<void(const std::string&)> handler) {
    dataHandler_ = handler;
}

bool TCPConnector::isConnected() const {
    return connected_;
}

// Convenience functions
void initializeComms() {
    globalComms->start();
}

void shutdownComms() {
    globalComms->stop();
}

bool sendAgentMessage(const std::string& channelId, const std::string& content, const std::string& sender) {
    Message message("", MessageType::TEXT, sender, "", content);
    return globalComms->sendMessage(channelId, message);
}

void setGlobalMessageReceiver(MessageHandler handler) {
    globalComms->setGlobalMessageHandler(handler);
}

} // namespace elizaos
