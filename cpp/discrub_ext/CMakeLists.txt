# Stage 6 - Tools and Automation placeholder - implementation planned
add_library(elizaos-discrub_ext STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-discrub_ext PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-discrub_ext 
    elizaos-core
)
