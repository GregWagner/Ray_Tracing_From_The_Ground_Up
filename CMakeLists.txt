cmake_minimum_required(VERSION 3.16)

project(rtf VERSION 1.0 LANGUAGES CXX DESCRIPTION "Ray Tracing from the Ground Up example project")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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
    ${CMAKE_CURRENT_SOURCE_DIR}/src/BRDFs
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Cameras
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GeometricObjects
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Lights
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Materials
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Tracers
    ${CMAKE_CURRENT_SOURCE_DIR}/src/UserInterface
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Utilities
    ${CMAKE_CURRENT_SOURCE_DIR}/src/World
)

target_link_libraries(wxraytracer PRIVATE ${wxWidgets_LIBRARIES})
