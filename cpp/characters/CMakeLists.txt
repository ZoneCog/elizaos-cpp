# Stage 3 - Application-specific placeholder - implementation planned
add_library(elizaos-characters STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-characters PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-characters 
    elizaos-core
)
