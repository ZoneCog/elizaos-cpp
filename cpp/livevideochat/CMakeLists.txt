# Stage 4 - Multimedia placeholder - implementation planned
add_library(elizaos-livevideochat STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-livevideochat PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-livevideochat 
    elizaos-core
)
