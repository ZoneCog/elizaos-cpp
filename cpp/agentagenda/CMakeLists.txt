# Stage 1 placeholder - will be implemented in Stage 3
add_library(elizaos-agentagenda STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-agentagenda PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-agentagenda 
    elizaos-core
)