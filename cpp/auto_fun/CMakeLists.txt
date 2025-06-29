# Stage 3 - Application-specific placeholder - implementation planned
add_library(elizaos-auto_fun STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-auto_fun PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-auto_fun 
    elizaos-core
)
