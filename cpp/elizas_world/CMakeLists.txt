# Stage 3 - Application-specific placeholder - implementation planned
add_library(elizaos-elizas_world STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-elizas_world PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-elizas_world 
    elizaos-core
)
