add_executable(rtf_tests
    math_test.cpp
    geometry_test.cpp
    world_stub.cpp
)

target_link_libraries(rtf_tests PRIVATE rtf_core GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(rtf_tests)