# Stage 3 - Application-specific placeholder - implementation planned
add_library(elizaos-autonomous_starter STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-autonomous_starter PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-autonomous_starter 
    elizaos-core
)
