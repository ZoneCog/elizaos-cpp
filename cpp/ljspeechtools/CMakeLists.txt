# Stage 4 - Multimedia placeholder - implementation planned
add_library(elizaos-ljspeechtools STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-ljspeechtools PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-ljspeechtools 
    elizaos-core
)
