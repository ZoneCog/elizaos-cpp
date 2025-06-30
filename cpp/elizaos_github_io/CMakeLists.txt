# Stage 5 - Web and Documentation placeholder - implementation planned
add_library(elizaos-elizaos_github_io STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-elizaos_github_io PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-elizaos_github_io 
    elizaos-core
)
