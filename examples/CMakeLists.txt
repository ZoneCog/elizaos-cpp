add_executable(elizaos_demo
    demo.cpp
)

target_include_directories(elizaos_demo PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos_demo
    elizaos-core
    elizaos-agentloop
    Threads::Threads
)