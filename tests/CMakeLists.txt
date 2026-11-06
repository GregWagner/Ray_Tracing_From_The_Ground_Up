add_executable(rtf_tests
    math_test.cpp
    geometry_test.cpp
    world_stub.cpp
)

target_link_libraries(rtf_tests PRIVATE rtf_core GTest::gtest_main)

if(ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	target_compile_options(rtf_tests PRIVATE
		-fsanitize=address,undefined
		-fno-omit-frame-pointer
		-g
	)
	target_link_options(rtf_tests PRIVATE
		-fsanitize=address,undefined
	)
endif()

include(GoogleTest)
gtest_discover_tests(rtf_tests)

if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(rtf_tests PRIVATE --coverage -O0 -g)
    target_link_options(rtf_tests PRIVATE --coverage)
endif()
