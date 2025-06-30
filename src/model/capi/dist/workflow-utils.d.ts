/**
 * Workflow Utilities for Defensive Error Handling
 *
 * This module provides utilities for GitHub Actions workflows to handle
 * common failure scenarios gracefully, particularly for session logging
 * and external API integrations.
 *
 * Fixes GitHub Issue #27: https://github.com/ZoneCog/elizaos-cpp/issues/27
 */
/**
 * Environment configuration for workflow error handling
 */
interface WorkflowConfig {
    sessionLogsEndpoint?: string;
    enableSessionLogging?: boolean;
    failOnSessionLogError?: boolean;
    retryCount?: number;
    timeoutMs?: number;
}
/**
 * Workflow context information
 */
interface WorkflowContext {
    workflowName?: string;
    runId?: string;
    actor?: string;
    repository?: string;
    event?: string;
    ref?: string;
}
/**
 * Main utility class for defensive workflow operations
 */
declare class WorkflowUtils {
    private config;
    private context;
    private sessionsClient;
    constructor(config?: WorkflowConfig);
    /**
     * Extract workflow context from environment variables
     */
    private extractWorkflowContext;
    /**
     * Safely upload session logs without failing the workflow
     */
    uploadSessionLogs(logs: any[], sessionId?: string, metadata?: Record<string, any>): Promise<boolean>;
    /**
     * Check if the session logging service is available
     */
    checkSessionLogHealth(): Promise<boolean>;
    /**
     * Set GitHub Action output safely
     */
    setOutput(name: string, value: string): void;
    /**
     * Set GitHub Action environment variable safely
     */
    setEnvVar(name: string, value: string): void;
    /**
     * Log warning with GitHub Actions annotation
     */
    logWarning(message: string, file?: string, line?: number): void;
    /**
     * Log error with GitHub Actions annotation
     */
    logError(message: string, file?: string, line?: number): void;
    /**
     * Exit gracefully with proper session log cleanup
     */
    exitGracefully(exitCode?: number, finalLogs?: any[], reason?: string): Promise<void>;
    /**
     * Wrap a function with defensive error handling
     */
    withDefensiveHandling<T>(operation: () => Promise<T>, operationName: string, options?: {
        failOnError?: boolean;
        logErrors?: boolean;
        retryCount?: number;
    }): Promise<T | null>;
}
/**
 * Factory function to create a WorkflowUtils instance with environment-based configuration
 */
export declare function createWorkflowUtils(): WorkflowUtils;
export { WorkflowUtils, type WorkflowConfig, type WorkflowContext };
export default WorkflowUtils;
//# sourceMappingURL=workflow-utils.d.ts.map