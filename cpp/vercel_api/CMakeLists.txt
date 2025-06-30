# Stage 5 - Web and Documentation placeholder - implementation planned
add_library(elizaos-vercel_api STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-vercel_api PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-vercel_api 
    elizaos-core
)
