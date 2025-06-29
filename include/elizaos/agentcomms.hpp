#pragma once

#include <string>
#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>

namespace elizaos {

/**
 * Message types for agent communication
 */
enum class MessageType {
    TEXT,
    COMMAND,
    RESPONSE,
    STATUS,
    ERROR
};

/**
 * Basic message structure for agent communication
 */
struct Message {
    std::string id;
    MessageType type;
    std::string sender;
    std::string receiver;
    std::string content;
    std::unordered_map<std::string, std::string> metadata;
    std::chrono::system_clock::time_point timestamp;
    
    Message(
        const std::string& id = "",
        MessageType type = MessageType::TEXT,
        const std::string& sender = "",
        const std::string& receiver = "",
        const std::string& content = ""
    );
};

/**
 * Message handler function type
 */
using MessageHandler = std::function<void(const Message&)>;

/**
 * Communication channel for message passing
 */
class CommChannel {
public:
    CommChannel(const std::string& channelId);
    ~CommChannel();
    
    /**
     * Send a message through this channel
     * @param message Message to send
     * @return True if message was queued successfully
     */
    bool sendMessage(const Message& message);
    
    /**
     * Register a handler for incoming messages
     * @param handler Function to call when messages arrive
     */
    void setMessageHandler(MessageHandler handler);
    
    /**
     * Start processing messages
     */
    void start();
    
    /**
     * Stop processing messages
     */
    void stop();
    
    /**
     * Get channel ID
     */
    const std::string& getChannelId() const { return channelId_; }
    
    /**
     * Check if channel is active
     */
    bool isActive() const { return active_; }
    
private:
    void processMessages();
    
    std::string channelId_;
    std::atomic<bool> active_;
    std::atomic<bool> stopRequested_;
    
    std::queue<Message> messageQueue_;
    std::mutex queueMutex_;
    std::condition_variable queueCondition_;
    
    MessageHandler messageHandler_;
    std::unique_ptr<std::thread> processingThread_;
};

/**
 * Communication manager for agent networking
 */
class AgentComms {
public:
    AgentComms();
    ~AgentComms();
    
    /**
     * Create a new communication channel
     * @param channelId Unique identifier for the channel
     * @return Shared pointer to the created channel
     */
    std::shared_ptr<CommChannel> createChannel(const std::string& channelId);
    
    /**
     * Get existing channel by ID
     * @param channelId Channel identifier
     * @return Shared pointer to channel, or nullptr if not found
     */
    std::shared_ptr<CommChannel> getChannel(const std::string& channelId);
    
    /**
     * Remove a channel
     * @param channelId Channel identifier
     */
    void removeChannel(const std::string& channelId);
    
    /**
     * Send a message to a specific channel
     * @param channelId Target channel
     * @param message Message to send
     * @return True if message was sent successfully
     */
    bool sendMessage(const std::string& channelId, const Message& message);
    
    /**
     * Broadcast a message to all channels
     * @param message Message to broadcast
     */
    void broadcastMessage(const Message& message);
    
    /**
     * Get list of active channel IDs
     */
    std::vector<std::string> getActiveChannels() const;
    
    /**
     * Set global message handler (receives all messages)
     * @param handler Function to call for all messages
     */
    void setGlobalMessageHandler(MessageHandler handler);
    
    /**
     * Start the communication system
     */
    void start();
    
    /**
     * Stop the communication system
     */
    void stop();
    
private:
    std::unordered_map<std::string, std::shared_ptr<CommChannel>> channels_;
    mutable std::mutex channelsMutex_;
    MessageHandler globalHandler_;
    std::atomic<bool> started_;
};

/**
 * Network connector interface for external communication
 */
class NetworkConnector {
public:
    virtual ~NetworkConnector() = default;
    
    /**
     * Connect to external service
     * @param connectionString Connection details
     * @return True if connection successful
     */
    virtual bool connect(const std::string& connectionString) = 0;
    
    /**
     * Disconnect from external service
     */
    virtual void disconnect() = 0;
    
    /**
     * Send data to external service
     * @param data Data to send
     * @return True if sent successfully
     */
    virtual bool sendData(const std::string& data) = 0;
    
    /**
     * Set handler for incoming data
     * @param handler Function to call when data arrives
     */
    virtual void setDataHandler(std::function<void(const std::string&)> handler) = 0;
    
    /**
     * Check if connected
     */
    virtual bool isConnected() const = 0;
};

/**
 * Simple TCP connector implementation
 */
class TCPConnector : public NetworkConnector {
public:
    TCPConnector();
    ~TCPConnector() override;
    
    bool connect(const std::string& connectionString) override;
    void disconnect() override;
    bool sendData(const std::string& data) override;
    void setDataHandler(std::function<void(const std::string&)> handler) override;
    bool isConnected() const override;
    
private:
    std::atomic<bool> connected_;
    std::function<void(const std::string&)> dataHandler_;
    // Note: Full TCP implementation would require platform-specific socket code
    // This is a basic framework for now
};

/**
 * Global communication manager instance
 */
extern std::shared_ptr<AgentComms> globalComms;

/**
 * Convenience functions for common communication operations
 */
void initializeComms();
void shutdownComms();
bool sendAgentMessage(const std::string& channelId, const std::string& content, const std::string& sender = "");
void setGlobalMessageReceiver(MessageHandler handler);

} // namespace elizaos