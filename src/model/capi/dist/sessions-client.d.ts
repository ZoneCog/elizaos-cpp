/**
 * Defensive Sessions Client with 404 Error Handling
 *
 * This module provides robust session log upload functionality that gracefully
 * handles endpoint unavailability (404 errors) without failing the entire workflow.
 *
 * Fixes GitHub Issue #27: https://github.com/ZoneCog/elizaos-cpp/issues/27
 */
interface SessionLogData {
    sessionId: string;
    logs: any[];
    timestamp: number;
    metadata?: Record<string, any>;
}
interface SessionUploadOptions {
    endpoint?: string;
    retries?: number;
    timeout?: number;
    failOnError?: boolean;
}
declare class SessionsClient {
    private defaultEndpoint;
    private defaultOptions;
    constructor(endpoint?: string, options?: SessionUploadOptions);
    /**
     * Upload session logs with defensive error handling
     * @param logData - The session log data to upload
     * @param options - Upload options (optional)
     * @returns Promise<boolean> - true if successful, false if failed but gracefully handled
     */
    uploadSessionLog(logData: SessionLogData, options?: SessionUploadOptions): Promise<boolean>;
    /**
     * Perform the actual HTTP upload
     */
    private performUpload;
    /**
     * Utility method for delays
     */
    private delay;
    /**
     * Health check for the session logging endpoint
     */
    healthCheck(endpoint?: string): Promise<boolean>;
}
export { SessionsClient, type SessionLogData, type SessionUploadOptions };
export default SessionsClient;
//# sourceMappingURL=sessions-client.d.ts.map