# Stage 1 placeholder - will be implemented in Stage 2
add_library(elizaos-agentbrowser STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-agentbrowser PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-agentbrowser 
    elizaos-core
)
