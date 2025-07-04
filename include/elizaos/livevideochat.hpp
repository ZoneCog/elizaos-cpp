#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <cstdint>

namespace elizaos {

/**
 * Video frame data structure
 */
struct VideoFrame {
    std::vector<uint8_t> data;
    int width;
    int height;
    int stride;
    std::string format; // e.g., "I420", "RGB24", "RGBA"
    int64_t timestamp_ms;
};

/**
 * Audio frame data structure for video chat
 */
struct AudioFrame {
    std::vector<float> samples;
    int sample_rate;
    int channels;
    int64_t timestamp_ms;
};

/**
 * Video chat configuration
 */
struct VideoChatConfig {
    int video_width = 640;
    int video_height = 480;
    int video_fps = 30;
    int video_bitrate = 1000000; // 1 Mbps
    
    int audio_sample_rate = 48000;
    int audio_channels = 2;
    int audio_bitrate = 128000; // 128 kbps
    
    bool enable_video = true;
    bool enable_audio = true;
    
    std::string stun_server = "stun:stun.l.google.com:19302";
    std::vector<std::string> turn_servers;
    
    std::string video_codec = "VP8";
    std::string audio_codec = "OPUS";
};

/**
 * Peer connection state
 */
enum class PeerConnectionState {
    New,
    Connecting,
    Connected,
    Disconnected,
    Failed,
    Closed
};

/**
 * Video chat session information
 */
struct SessionInfo {
    std::string session_id;
    std::string peer_id;
    PeerConnectionState state;
    std::string local_sdp;
    std::string remote_sdp;
    int64_t start_time_ms;
    int64_t last_activity_ms;
};

/**
 * Media stream callbacks
 */
class MediaStreamCallbacks {
public:
    virtual ~MediaStreamCallbacks() = default;
    
    /**
     * Called when a video frame is received
     */
    virtual void onVideoFrame(const std::string& peer_id, const VideoFrame& frame) = 0;
    
    /**
     * Called when an audio frame is received
     */
    virtual void onAudioFrame(const std::string& peer_id, const AudioFrame& frame) = 0;
    
    /**
     * Called when peer connection state changes
     */
    virtual void onPeerConnectionStateChange(
        const std::string& peer_id,
        PeerConnectionState state
    ) = 0;
    
    /**
     * Called when an error occurs
     */
    virtual void onError(const std::string& peer_id, const std::string& error) = 0;
};

/**
 * Video capture interface
 */
class VideoCapture {
public:
    virtual ~VideoCapture() = default;
    
    /**
     * Start video capture
     */
    virtual bool start() = 0;
    
    /**
     * Stop video capture
     */
    virtual void stop() = 0;
    
    /**
     * Get the next video frame
     */
    virtual VideoFrame getNextFrame() = 0;
    
    /**
     * Set capture configuration
     */
    virtual bool setConfig(int width, int height, int fps) = 0;
    
    /**
     * Check if capture is active
     */
    virtual bool isActive() const = 0;
};

/**
 * Audio capture interface
 */
class AudioCapture {
public:
    virtual ~AudioCapture() = default;
    
    /**
     * Start audio capture
     */
    virtual bool start() = 0;
    
    /**
     * Stop audio capture
     */
    virtual void stop() = 0;
    
    /**
     * Get the next audio frame
     */
    virtual AudioFrame getNextFrame() = 0;
    
    /**
     * Set capture configuration
     */
    virtual bool setConfig(int sample_rate, int channels) = 0;
    
    /**
     * Check if capture is active
     */
    virtual bool isActive() const = 0;
};

/**
 * WebRTC peer connection wrapper
 */
class WebRTCPeerConnection {
public:
    WebRTCPeerConnection();
    ~WebRTCPeerConnection();
    
    /**
     * Initialize the peer connection
     */
    bool initialize(const VideoChatConfig& config);
    
    /**
     * Create an offer for initiating connection
     */
    std::string createOffer();
    
    /**
     * Create an answer for responding to offer
     */
    std::string createAnswer(const std::string& offer);
    
    /**
     * Set remote description
     */
    bool setRemoteDescription(const std::string& sdp);
    
    /**
     * Set local description
     */
    bool setLocalDescription(const std::string& sdp);
    
    /**
     * Add ICE candidate
     */
    bool addIceCandidate(const std::string& candidate);
    
    /**
     * Get connection state
     */
    PeerConnectionState getState() const;
    
    /**
     * Send video frame
     */
    bool sendVideoFrame(const VideoFrame& frame);
    
    /**
     * Send audio frame
     */
    bool sendAudioFrame(const AudioFrame& frame);
    
    /**
     * Set callbacks for receiving media
     */
    void setCallbacks(std::shared_ptr<MediaStreamCallbacks> callbacks);
    
    /**
     * Close the connection
     */
    void close();
    
private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

/**
 * Video chat session manager
 */
class VideoChatSession {
public:
    VideoChatSession();
    ~VideoChatSession();
    
    /**
     * Initialize session with configuration
     */
    bool initialize(const VideoChatConfig& config);
    
    /**
     * Start a new session as initiator
     */
    bool startSession(const std::string& peer_id);
    
    /**
     * Join an existing session
     */
    bool joinSession(const std::string& session_id, const std::string& peer_id);
    
    /**
     * Handle incoming offer
     */
    std::string handleOffer(const std::string& peer_id, const std::string& offer);
    
    /**
     * Handle incoming answer
     */
    bool handleAnswer(const std::string& peer_id, const std::string& answer);
    
    /**
     * Handle ICE candidate
     */
    bool handleIceCandidate(
        const std::string& peer_id,
        const std::string& candidate
    );
    
    /**
     * Set media stream callbacks
     */
    void setCallbacks(std::shared_ptr<MediaStreamCallbacks> callbacks);
    
    /**
     * Enable/disable video
     */
    void enableVideo(bool enabled);
    
    /**
     * Enable/disable audio
     */
    void enableAudio(bool enabled);
    
    /**
     * Get session information
     */
    SessionInfo getSessionInfo() const;
    
    /**
     * Get list of connected peers
     */
    std::vector<std::string> getConnectedPeers() const;
    
    /**
     * End session
     */
    void endSession();
    
private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

/**
 * Main LiveVideoChat interface
 */
class LiveVideoChat {
public:
    LiveVideoChat();
    ~LiveVideoChat();
    
    /**
     * Initialize the video chat system
     */
    bool initialize(const VideoChatConfig& config = {});
    
    /**
     * Create a new video chat session
     */
    std::shared_ptr<VideoChatSession> createSession(const std::string& session_id);
    
    /**
     * Get existing session
     */
    std::shared_ptr<VideoChatSession> getSession(const std::string& session_id);
    
    /**
     * Remove session
     */
    void removeSession(const std::string& session_id);
    
    /**
     * List active sessions
     */
    std::vector<std::string> getActiveSessions() const;
    
    /**
     * Set global media callbacks
     */
    void setGlobalCallbacks(std::shared_ptr<MediaStreamCallbacks> callbacks);
    
    /**
     * Get video capture interface
     */
    std::shared_ptr<VideoCapture> getVideoCapture();
    
    /**
     * Get audio capture interface
     */
    std::shared_ptr<AudioCapture> getAudioCapture();
    
    /**
     * Shutdown the system
     */
    void shutdown();
    
private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace elizaos