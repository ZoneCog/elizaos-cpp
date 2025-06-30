# Defensive Session Logging Solution

This directory contains a robust solution for handling session log upload failures in GitHub Actions workflows, specifically addressing issue [#27](https://github.com/ZoneCog/elizaos-cpp/issues/27).

## Problem

GitHub Actions workflows were failing when external session logging services returned HTTP 404 errors. The specific error was:

```
Error adding session logs (Request ID ... failed): 404
```

This caused workflows to abort with "forceExit is shutting down the process" instead of completing successfully.

## Solution

The solution implements defensive error handling that gracefully handles endpoint unavailability without failing the entire workflow.

### Key Components

1. **`sessions-client.ts`** - Defensive session logging client with 404 error handling
2. **`workflow-utils.ts`** - Higher-level utilities for workflow error handling
3. **`sessions-client.test.ts`** - Comprehensive test suite
4. **`defensive-session-logging.yml`** - Example workflow demonstrating the solution

### Features

- ✅ **Graceful 404 handling** - Logs warnings but doesn't fail the workflow
- ✅ **Network error resilience** - Handles connection issues gracefully
- ✅ **Configurable retry logic** - Exponential backoff for transient errors
- ✅ **Comprehensive logging** - Clear diagnostic messages for debugging
- ✅ **Optional strict mode** - Can be configured to fail on errors if needed
- ✅ **Health checks** - Endpoint availability testing
- ✅ **Full test coverage** - Validates all error scenarios

## Usage

### Basic Usage

```typescript
import { SessionsClient } from './sessions-client';

const client = new SessionsClient('https://your-session-endpoint.com/logs');

const logData = {
  sessionId: 'session-123',
  logs: ['Log entry 1', 'Log entry 2'],
  timestamp: Date.now()
};

// Will return false on 404 but won't throw an error
const success = await client.uploadSessionLog(logData);
```

### Workflow Integration

```typescript
import { createWorkflowUtils } from './workflow-utils';

const utils = createWorkflowUtils();

// Upload logs safely without failing the workflow
await utils.uploadSessionLogs(['Log entry'], 'session-id');

// Check if logging service is available
const isHealthy = await utils.checkSessionLogHealth();
```

### GitHub Actions Workflow

```yaml
- name: Upload session logs (defensive)
  continue-on-error: true
  run: |
    node src/model/capi/sessions-client.js
```

## Configuration

Environment variables for configuration:

- `SESSION_LOGS_ENDPOINT` - The session logging endpoint URL
- `ENABLE_SESSION_LOGGING` - Enable/disable session logging (default: true)
- `FAIL_ON_SESSION_LOG_ERROR` - Fail workflow on session log errors (default: false)
- `SESSION_LOG_RETRY_COUNT` - Number of retries for failed requests (default: 3)
- `SESSION_LOG_TIMEOUT_MS` - Request timeout in milliseconds (default: 10000)

## Error Handling Strategy

| Error Type | Status Code | Behavior | Retries |
|------------|-------------|----------|---------|
| Not Found | 404 | Log warning, continue | No |
| Client Error | 400-499 | Log error, continue | No |
| Server Error | 500+ | Log warning, retry | Yes |
| Network Error | N/A | Log warning, continue | No |
| Timeout | N/A | Log warning, retry | Yes |

## Testing

Run the test suite to verify defensive error handling:

```bash
cd src/model/capi
npm install --save-dev jest @types/jest ts-jest
npx jest sessions-client.test.ts --coverage
```

## Example Workflow

See `.github/workflows/defensive-session-logging.yml` for a complete example workflow that demonstrates:

- Testing different error scenarios
- Workflow continuation despite logging failures
- Proper error handling and reporting

## Migration Guide

To migrate existing workflows that might be affected by session logging failures:

1. **Add defensive client**: Include `sessions-client.ts` in your project
2. **Update workflows**: Add `continue-on-error: true` to session logging steps
3. **Replace calls**: Use the defensive client instead of direct API calls
4. **Monitor logs**: Check for warning messages about endpoint availability

## Best Practices

1. **Always use defensive error handling** for non-critical operations like logging
2. **Configure appropriate timeouts** to prevent workflows from hanging
3. **Monitor endpoint health** before attempting uploads
4. **Use meaningful error messages** for debugging
5. **Test error scenarios** to ensure graceful handling

## Implementation Details

The solution follows these principles:

- **Fail fast on client errors** (400-499) - don't retry
- **Retry on server errors** (500+) - might be transient
- **Never fail on 404** - endpoint might be optional or misconfigured
- **Always continue workflow** - session logging is non-critical
- **Provide clear diagnostics** - help with troubleshooting

This ensures that workflows remain robust and don't fail due to optional session logging services being unavailable.