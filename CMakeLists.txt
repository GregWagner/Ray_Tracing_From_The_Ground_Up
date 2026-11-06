cmake_minimum_required(VERSION 3.16)

project(rtf VERSION 1.0 LANGUAGES CXX DESCRIPTION "Ray Tracing from the Ground Up example project")

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.0")
    message(FATAL_ERROR "GCC 9.0 or newer is required")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.0")
    message(FATAL_ERROR "Clang 9.0 or newer is required")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for clang-tidy / tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Optional clang-tidy integration
option(ENABLE_CLANG_TIDY "Run clang-tidy during the build" ON)

# Optional tests
option(BUILD_TESTS "Build unit tests" ON)

# Optional code coverage integration
option(ENABLE_COVERAGE "Enable gcov/lcov code coverage reporting for tests" ON)

# Optional sanitizer integration
option(ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" ON)
if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if(CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}" "--removed-arg=-mno-direct-extern-access")
    else()
        message(WARNING "clang-tidy not found; ENABLE_CLANG_TIDY ignored")
    endif()
endif()

find_package(Qt6 6.2 REQUIRED COMPONENTS Widgets)

set(RTF_CORE_SOURCES
    src/BRDFs/BRDF.cpp
    src/BRDFs/Lambertian.cpp
    src/Cameras/Camera.cpp
    src/Cameras/Pinhole.cpp
    src/GeometricObjects/GeometricObject.cpp
    src/GeometricObjects/Plane.cpp
    src/GeometricObjects/Sphere.cpp
    src/Lights/Ambient.cpp
    src/Lights/Directional.cpp
    src/Lights/Light.cpp
    src/Materials/Material.cpp
    src/Materials/Matte.cpp
    src/Tracers/MultipleObjects.cpp
    src/Tracers/RayCast.cpp
    src/Tracers/SingleSphere.cpp
    src/Tracers/Tracer.cpp
    src/Utilities/Matrix.cpp
    src/Utilities/Normal.cpp
    src/Utilities/Point2D.cpp
    src/Utilities/Point3D.cpp
    src/Utilities/Ray.cpp
    src/Utilities/RGBColor.cpp
    src/Utilities/ShadeRec.cpp
    src/Utilities/Vector3D.cpp
    src/World/ViewPlane.cpp
    src/World/World.cpp
)

add_library(rtf_core STATIC ${RTF_CORE_SOURCES})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(qtraytracer
    src/UserInterface/qtraytracer.cpp
    include/UserInterface/qtraytracer.hpp
)

target_link_libraries(qtraytracer PRIVATE rtf_core Qt6::Widgets)

if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_link_options(qtraytracer PRIVATE --coverage)
endif()

target_include_directories(rtf_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/BRDFs
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Cameras
    ${CMAKE_CURRENT_SOURCE_DIR}/include/GeometricObjects
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Lights
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Materials
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Tracers
    ${CMAKE_CURRENT_SOURCE_DIR}/include/UserInterface
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Utilities
    ${CMAKE_CURRENT_SOURCE_DIR}/include/World
)



# Strict compiler warnings (no source changes required)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    foreach(tgt rtf_core qtraytracer)
        target_compile_options(${tgt} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wshadow
            -Wnon-virtual-dtor
            -Woverloaded-virtual
        )
    endforeach()
endif()

# Sanitizers
if(ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    foreach(tgt rtf_core qtraytracer)
        target_compile_options(${tgt} PRIVATE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
            -g
        )
    endforeach()
    target_link_options(qtraytracer PRIVATE
        -fsanitize=address,undefined
    )
    target_link_options(rtf_core PRIVATE
        -fsanitize=address,undefined
    )
endif()

# Code coverage flags
if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    foreach(tgt rtf_core)
        target_compile_options(${tgt} PRIVATE --coverage -O0 -g)
        target_link_options(${tgt} PRIVATE --coverage)
    endforeach()
endif()

# clang-format helper targets
if(BUILD_TESTS)
    find_package(GTest CONFIG REQUIRED)
    enable_testing()
    add_subdirectory(tests)
endif()

find_program(CLANG_FORMAT_EXE NAMES clang-format)
if(CLANG_FORMAT_EXE)
    file(GLOB_RECURSE FORMAT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
    )
    list(FILTER FORMAT_SOURCES EXCLUDE REGEX "\\.xpm$")
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE} -i ${FORMAT_SOURCES}
        COMMENT "Running clang-format on source files"
    )
    add_custom_target(check-format
        COMMAND ${CLANG_FORMAT_EXE} --dry-run --Werror ${FORMAT_SOURCES}
        COMMENT "Checking clang-format compliance"
    )
endif()

# Code coverage report target
if(BUILD_TESTS AND ENABLE_COVERAGE)
    find_program(LCOV_EXE NAMES lcov)
    find_program(GENHTML_EXE NAMES genhtml)
    if(LCOV_EXE AND GENHTML_EXE)
        add_custom_target(coverage
            COMMAND ${LCOV_EXE} --directory ${CMAKE_BINARY_DIR} --zerocounters
            COMMAND $<TARGET_FILE:rtf_tests>
            COMMAND ${LCOV_EXE} --ignore-errors inconsistent --directory ${CMAKE_BINARY_DIR} --capture --output-file ${CMAKE_BINARY_DIR}/coverage.info
            COMMAND ${LCOV_EXE} --ignore-errors inconsistent --remove ${CMAKE_BINARY_DIR}/coverage.info '/usr/*' '*/tests/*' --output-file ${CMAKE_BINARY_DIR}/coverage.info
            COMMAND ${GENHTML_EXE} ${CMAKE_BINARY_DIR}/coverage.info --output-directory ${CMAKE_BINARY_DIR}/coverage_report
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generating code coverage report"
        )
    endif()
endif()
