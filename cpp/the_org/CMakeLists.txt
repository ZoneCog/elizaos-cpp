# Stage 3 - Application-specific placeholder - implementation planned
add_library(elizaos-the_org STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-the_org PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-the_org 
    elizaos-core
)
