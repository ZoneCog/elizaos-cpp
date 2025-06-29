# ElizaOS C++ Build Instructions

## Prerequisites

- CMake 3.16 or higher
- C++17 compatible compiler (GCC 8+, Clang 10+, MSVC 2019+)
- Git (for dependency fetching)

## Quick Start

```bash
# Clone the repository (if not already done)
git clone <repository-url>
cd elizaos-cpp

# Create build directory
mkdir build
cd build

# Configure the project
cmake ..

# Build all targets
cmake --build . -j$(nproc)

# Run tests
ctest

# Build with examples (optional)
cmake -DBUILD_EXAMPLES=ON ..
cmake --build .

# Run demo
./examples/elizaos_demo
```

## Build Options

### Debug Build
```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
```

### Release Build (default)
```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

### Run Specific Tests
```bash
# Run all tests
ctest

# Run with verbose output
ctest --verbose

# Run specific test
ctest -R CoreTest

# Run failed tests with output
ctest --rerun-failed --output-on-failure
```

## Available Targets

- `elizaos-core`: Core data structures and interfaces
- `elizaos-agentloop`: Agent loop execution system
- `elizaos_tests`: Unit test executable
- Various placeholder libraries for future implementation stages

## Current Implementation Status

### ✅ Stage 1 - Core Logic (COMPLETE)
- Core data structures (Memory, State, Agent)
- AgentLoop with threading and pause/resume functionality
- Comprehensive unit tests
- CMake build system

### 🚧 Stage 2-6 - Future Implementation
- Placeholder modules created for all planned components
- Ready for incremental development

## Integration with Existing Code

The C++ implementation is designed to run alongside the existing TypeScript/Python code without conflicts. All existing functionality remains intact while the C++ modules provide additional performance and capabilities.

## Contributing

When adding new C++ modules:

1. Follow the existing directory structure under `cpp/`
2. Add corresponding CMakeLists.txt
3. Include comprehensive unit tests
4. Update this documentation

## Troubleshooting

### Common Issues

1. **Missing compiler**: Install GCC, Clang, or MSVC
2. **CMake not found**: Install CMake 3.16+
3. **Build failures**: Check compiler C++17 support
4. **Test failures**: Some timing-sensitive tests may occasionally fail in CI environments

### Platform-Specific Notes

#### Linux/macOS
```bash
# Install dependencies (Ubuntu/Debian)
sudo apt-get install build-essential cmake

# Install dependencies (macOS)
brew install cmake
```

#### Windows
- Use Visual Studio 2019+ or install MinGW-w64
- Ensure CMake is in PATH
- Consider using Visual Studio Code with CMake extension