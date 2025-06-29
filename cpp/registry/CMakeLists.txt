# Stage 3 - Application-specific placeholder - implementation planned
add_library(elizaos-registry STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-registry PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-registry 
    elizaos-core
)
