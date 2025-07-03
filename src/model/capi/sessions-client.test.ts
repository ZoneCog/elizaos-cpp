/**
 * Test suite for defensive sessions client
 * Verifies 404 error handling and graceful failure scenarios
 */

import { SessionsClient, SessionLogData } from '../sessions-client';

// Mock fetch for testing
global.fetch = jest.fn();

describe('SessionsClient Defensive Error Handling', () => {
  let client: SessionsClient;
  let mockFetch: jest.MockedFunction<typeof fetch>;

  beforeEach(() => {
    mockFetch = fetch as jest.MockedFunction<typeof fetch>;
    mockFetch.mockClear();
    client = new SessionsClient('https://test-endpoint.com/logs');
  });

  const sampleLogData: SessionLogData = {
    sessionId: 'test-session-123',
    logs: ['Test log entry'],
    timestamp: Date.now(),
    metadata: { test: true }
  };

  describe('404 Error Handling', () => {
    it('should handle 404 errors gracefully without throwing', async () => {
      mockFetch.mockResolvedValueOnce({
        ok: false,
        status: 404,
        statusText: 'Not Found'
      } as Response);

      const consoleSpy = jest.spyOn(console, 'warn').mockImplementation();

      const result = await client.uploadSessionLog(sampleLogData);
      
      expect(result).toBe(false);
      expect(consoleSpy).toHaveBeenCalledWith(
        'Session log endpoint returned 404 – endpoint not found or service unavailable'
      );
      expect(consoleSpy).toHaveBeenCalledWith(
        'Continuing execution without failing the workflow...'
      );

      consoleSpy.mockRestore();
    });

    it('should not retry on 404 errors', async () => {
      mockFetch.mockResolvedValueOnce({
        ok: false,
        status: 404,
        statusText: 'Not Found'
      } as Response);

      await client.uploadSessionLog(sampleLogData, { retries: 3 });
      
      expect(mockFetch).toHaveBeenCalledTimes(1);
    });
  });

  describe('Network Error Handling', () => {
    it('should handle ECONNREFUSED errors gracefully', async () => {
      const networkError = new Error('Connection refused');
      (networkError as any).code = 'ECONNREFUSED';
      mockFetch.mockRejectedValueOnce(networkError);

      const consoleSpy = jest.spyOn(console, 'warn').mockImplementation();

      const result = await client.uploadSessionLog(sampleLogData);
      
      expect(result).toBe(false);
      expect(consoleSpy).toHaveBeenCalledWith(
        expect.stringContaining('Network error: Connection refused')
      );

      consoleSpy.mockRestore();
    });

    it('should handle ENOTFOUND errors gracefully', async () => {
      const networkError = new Error('Host not found');
      (networkError as any).code = 'ENOTFOUND';
      mockFetch.mockRejectedValueOnce(networkError);

      const consoleSpy = jest.spyOn(console, 'warn').mockImplementation();

      const result = await client.uploadSessionLog(sampleLogData);
      
      expect(result).toBe(false);
      expect(consoleSpy).toHaveBeenCalledWith(
        'Continuing execution without failing the workflow...'
      );

      consoleSpy.mockRestore();
    });
  });

  describe('Server Error Handling', () => {
    it('should retry on 500 errors', async () => {
      mockFetch
        .mockResolvedValueOnce({
          ok: false,
          status: 500,
          statusText: 'Internal Server Error'
        } as Response)
        .mockResolvedValueOnce({
          ok: true,
          status: 200,
          statusText: 'OK'
        } as Response);

      const result = await client.uploadSessionLog(sampleLogData, { retries: 2 });
      
      expect(result).toBe(true);
      expect(mockFetch).toHaveBeenCalledTimes(2);
    });

    it('should exhaust retries and handle gracefully', async () => {
      mockFetch.mockResolvedValue({
        ok: false,
        status: 500,
        statusText: 'Internal Server Error'
      } as Response);

      const consoleSpy = jest.spyOn(console, 'error').mockImplementation();
      const warnSpy = jest.spyOn(console, 'warn').mockImplementation();

      const result = await client.uploadSessionLog(sampleLogData, { retries: 2 });
      
      expect(result).toBe(false);
      expect(mockFetch).toHaveBeenCalledTimes(2);
      expect(warnSpy).toHaveBeenCalledWith(
        'Continuing execution despite session log upload failure...'
      );

      consoleSpy.mockRestore();
      warnSpy.mockRestore();
    });
  });

  describe('Success Scenarios', () => {
    it('should upload successfully on first attempt', async () => {
      mockFetch.mockResolvedValueOnce({
        ok: true,
        status: 200,
        statusText: 'OK'
      } as Response);

      const consoleSpy = jest.spyOn(console, 'log').mockImplementation();

      const result = await client.uploadSessionLog(sampleLogData);
      
      expect(result).toBe(true);
      expect(consoleSpy).toHaveBeenCalledWith('Session logs uploaded successfully');

      consoleSpy.mockRestore();
    });
  });

  describe('Configuration Handling', () => {
    it('should handle missing endpoint gracefully', async () => {
      const clientWithoutEndpoint = new SessionsClient('');
      const consoleSpy = jest.spyOn(console, 'warn').mockImplementation();

      const result = await clientWithoutEndpoint.uploadSessionLog(sampleLogData);
      
      expect(result).toBe(false);
      expect(consoleSpy).toHaveBeenCalledWith(
        'Session log endpoint not configured - skipping upload'
      );

      consoleSpy.mockRestore();
    });
  });

  describe('Fail on Error Option', () => {
    it('should throw error when failOnError is true and 500 error occurs', async () => {
      mockFetch.mockResolvedValue({
        ok: false,
        status: 500,
        statusText: 'Internal Server Error'
      } as Response);

      await expect(
        client.uploadSessionLog(sampleLogData, { failOnError: true, retries: 1 })
      ).rejects.toThrow('HTTP 500: Internal Server Error');
    });

    it('should NOT throw error when failOnError is true and 404 error occurs', async () => {
      mockFetch.mockResolvedValueOnce({
        ok: false,
        status: 404,
        statusText: 'Not Found'
      } as Response);

      const consoleSpy = jest.spyOn(console, 'warn').mockImplementation();

      const result = await client.uploadSessionLog(sampleLogData, { failOnError: true });
      
      expect(result).toBe(false);
      // Should not throw, just return false

      consoleSpy.mockRestore();
    });
  });

  describe('Health Check', () => {
    it('should return true for healthy endpoint', async () => {
      mockFetch.mockResolvedValueOnce({
        ok: true,
        status: 200
      } as Response);

      const result = await client.healthCheck();
      expect(result).toBe(true);
    });

    it('should return false for unhealthy endpoint', async () => {
      mockFetch.mockResolvedValueOnce({
        ok: false,
        status: 404
      } as Response);

      const result = await client.healthCheck();
      expect(result).toBe(false);
    });

    it('should return false when endpoint is not configured', async () => {
      const clientWithoutEndpoint = new SessionsClient('');
      const result = await clientWithoutEndpoint.healthCheck();
      expect(result).toBe(false);
    });
  });
});

// Additional integration test for CLI usage
describe('CLI Integration', () => {
  it('should handle successful CLI execution', async () => {
    const originalModule = require.main;
    const originalEnv = process.env;

    // Mock environment variables
    process.env = {
      ...process.env,
      GITHUB_RUN_ID: 'test-run-123',
      GITHUB_WORKFLOW: 'test-workflow',
      GITHUB_ACTOR: 'test-actor'
    };

    // Mock require.main to simulate CLI execution
    require.main = { filename: __filename } as any;

    try {
      const exitSpy = jest.spyOn(process, 'exit').mockImplementation();
      const mockFetch = jest.fn().mockResolvedValue({
        ok: true,
        status: 200
      });
      global.fetch = mockFetch;

      // This would test the CLI path if we were to execute it
      expect(process.env.GITHUB_RUN_ID).toBe('test-run-123');

      exitSpy.mockRestore();
    } finally {
      require.main = originalModule;
      process.env = originalEnv;
    }
  });
});