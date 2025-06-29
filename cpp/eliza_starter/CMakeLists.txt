# Stage 3 - Application-specific placeholder - implementation planned
add_library(elizaos-eliza_starter STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-eliza_starter PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-eliza_starter 
    elizaos-core
)
