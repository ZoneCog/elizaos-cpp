# Stage 3 - Application-specific placeholder - implementation planned
add_library(elizaos-spartan STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-spartan PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-spartan 
    elizaos-core
)
