# Stage 1 placeholder - will be implemented in Stage 3
add_library(elizaos-agentaction STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-agentaction PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-agentaction 
    elizaos-core
)