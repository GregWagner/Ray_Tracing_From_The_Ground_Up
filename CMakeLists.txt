cmake_minimum_required(VERSION 3.16)

project(rtf VERSION 1.0 LANGUAGES CXX DESCRIPTION "Ray Tracing from the Ground Up example project")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for clang-tidy / tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Optional clang-tidy integration
option(ENABLE_CLANG_TIDY "Run clang-tidy during the build" OFF)
if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if(CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
    else()
        message(WARNING "clang-tidy not found; ENABLE_CLANG_TIDY ignored")
    endif()
endif()

find_package(wxWidgets CONFIG REQUIRED COMPONENTS xrc html qa xml net core base)

add_executable(wxraytracer
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
    src/UserInterface/wxraytracer.cpp
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

target_include_directories(wxraytracer PRIVATE
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

target_link_libraries(wxraytracer PRIVATE ${wxWidgets_LIBRARIES})

# Strict compiler warnings (no source changes required)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(wxraytracer PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wnon-virtual-dtor
        -Woverloaded-virtual
    )
endif()

# clang-format helper targets
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
