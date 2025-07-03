add_executable(elizaos_tests
    src/test_core.cpp
    src/test_agentloop.cpp
    src/test_cognitive_primitives.cpp
    src/test_agentlogger.cpp
    src/test_agentcomms.cpp
    src/test_agentmemory.cpp
    src/test_attention_allocation.cpp
)

target_include_directories(elizaos_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(elizaos_tests
    elizaos-core
    elizaos-agentloop
    elizaos-agentmemory
    elizaos-agentlogger
    elizaos-agentcomms
    gtest_main
    gmock_main
    Threads::Threads
)

# Add tests to CTest
include(GoogleTest)
gtest_discover_tests(elizaos_tests)