# Stage 6 - Tools and Automation placeholder - implementation planned
add_library(elizaos-plugins_automation STATIC
    src/placeholder.cpp
)

target_include_directories(elizaos-plugins_automation PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos-plugins_automation 
    elizaos-core
)
