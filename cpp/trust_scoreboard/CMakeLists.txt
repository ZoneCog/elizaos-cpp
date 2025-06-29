# Stage 3 - Application-specific placeholder - implementation planned
add_library(elizaos-trust_scoreboard STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-trust_scoreboard PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-trust_scoreboard 
    elizaos-core
)
