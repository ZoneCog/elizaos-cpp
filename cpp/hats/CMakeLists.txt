# Stage 3 - Application-specific placeholder - implementation planned
add_library(elizaos-hats STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-hats PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-hats 
    elizaos-core
)
