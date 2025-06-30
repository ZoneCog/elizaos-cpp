# Stage 3 - Application-specific placeholder - implementation planned
add_library(elizaos-workgroups STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-workgroups PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-workgroups 
    elizaos-core
)
