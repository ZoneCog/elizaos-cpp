# Stage 3 - Application-specific placeholder - implementation planned
add_library(elizaos-autofun_idl STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-autofun_idl PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-autofun_idl 
    elizaos-core
)
