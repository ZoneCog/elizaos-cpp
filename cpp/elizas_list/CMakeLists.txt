# Stage 3 - Application-specific placeholder - implementation planned
add_library(elizaos-elizas_list STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-elizas_list PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-elizas_list 
    elizaos-core
)
