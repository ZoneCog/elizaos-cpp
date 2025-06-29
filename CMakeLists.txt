cmake_minimum_required(VERSION 3.16)

project(ElizaOS-CPP 
    VERSION 1.0.0
    DESCRIPTION "C++ implementation of ElizaOS agent framework"
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler-specific options
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -O0)
    endif()
endif()

# Find packages
find_package(Threads REQUIRED)

# Enable testing
enable_testing()

# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Core modules - organized by priority for Stage 1-2 migration
add_subdirectory(cpp/core)           # Core data structures and interfaces
add_subdirectory(cpp/agentloop)      # Main event loop (Stage 1 - Core Logic)
add_subdirectory(cpp/agentaction)    # Action processing (Stage 3 - Application-specific)
add_subdirectory(cpp/agentagenda)    # Task scheduling (Stage 3 - Application-specific)
add_subdirectory(cpp/agentcomms)     # Communications (Stage 2 - Infrastructure)
add_subdirectory(cpp/agentlogger)    # Logging system (Stage 2 - Infrastructure)
add_subdirectory(cpp/agentbrowser)   # Browser automation (Stage 3 - Application-specific)
add_subdirectory(cpp/agentmemory)    # Memory management (Stage 1 - Core Logic)

# Multimedia modules - Stage 4
# add_subdirectory(cpp/ljspeechtools)  # Speech processing (Stage 4 - Multimedia)
# add_subdirectory(cpp/livevideochat)  # Video chat (Stage 4 - Multimedia)

# Testing
add_subdirectory(cpp/tests)

# Add example executable (optional)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Installation
install(TARGETS elizaos-core elizaos-agentloop
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# Generate package config
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/ElizaOSConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# Print configuration summary
message(STATUS "ElizaOS-CPP Configuration Summary:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Install prefix: ${CMAKE_INSTALL_PREFIX}")