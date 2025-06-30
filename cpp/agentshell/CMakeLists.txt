# Stage 2 - Infrastructure placeholder - implementation planned
add_library(elizaos-agentshell STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-agentshell PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-agentshell 
    elizaos-core
)
