# AgentMemory - Memory management system for agent interactions
add_library(elizaos-agentmemory STATIC
    src/agentmemory.cpp
)

target_include_directories(elizaos-agentmemory PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-agentmemory 
    elizaos-core
    Threads::Threads
)
