# Stage 6 - Tools and Automation placeholder - implementation planned
add_library(elizaos-discord_summarizer STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-discord_summarizer PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-discord_summarizer 
    elizaos-core
)
