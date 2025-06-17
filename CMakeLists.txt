cmake_minimum_required(VERSION 3.14)

project(raytracer
    VERSION 0.1
    DESCRIPTION "A simple raytracer"
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -- Build Primitives --
# -- Primitive Manager --
add_library(primitives SHARED
    src/tools/Error.cpp
    src/tools/Error.hpp
    src/tools/dlManager.cpp
    src/tools/dlManager.hpp
    src/Primitives/IPrimitive.hpp
    src/Primitives/PrimitiveManager.cpp
    src/Primitives/PrimitiveManager.hpp
)

set_target_properties(primitives PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/plugins"
    OUTPUT_NAME "primitiveManager"
    PREFIX ""
)

# -- Sphere --
add_library(sphere SHARED
    src/Materials/Flat.hpp
    src/Materials/Metal.hpp
    src/Primitives/Vector3D.hpp
    src/Primitives/Vector3D.cpp
    src/Materials/IMaterials.hpp
    src/Primitives/Sphere/Sphere.cpp
    src/Primitives/Sphere/Sphere.hpp
    src/Primitives/PrimitiveList.hpp
)

set_target_properties(sphere PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/plugins"
    OUTPUT_NAME "sphere"
    PREFIX ""
)

# -- Plane --

add_library(plane SHARED
    src/Materials/Flat.hpp
    src/Materials/Metal.hpp
    src/Primitives/Vector3D.cpp
    src/Primitives/Vector3D.hpp
    src/Materials/IMaterials.hpp
    src/Primitives/Plane/Plane.cpp
    src/Primitives/Plane/Plane.hpp
    src/Primitives/PrimitiveList.hpp
)

set_target_properties(plane PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/plugins"
    OUTPUT_NAME "plane"
    PREFIX ""
)

# -- Cube --

add_library(cube SHARED
    src/Materials/Flat.hpp
    src/Materials/Metal.hpp
    src/Primitives/Vector3D.cpp
    src/Primitives/Vector3D.hpp
    src/Materials/IMaterials.hpp
    src/Primitives/Cube/Cube.cpp
    src/Primitives/Cube/Cube.hpp
    src/Primitives/PrimitiveList.hpp
)

set_target_properties(cube PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/plugins"
    OUTPUT_NAME "cube"
    PREFIX ""
)

# -- Build executable --

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG++ REQUIRED libconfig++)

add_executable(raytracer
    src/Ray.hpp
    src/Ray.cpp
    src/main.cpp
    src/Camera.hpp
    src/Camera.cpp
    src/tools/Error.cpp
    src/tools/Error.hpp
    src/Materials/Flat.hpp
    src/Builder/Builder.cpp
    src/Builder/Builder.hpp
    src/tools/dlManager.cpp
    src/tools/dlManager.hpp
    src/Materials/Metal.hpp
    src/Primitives/Vector3D.hpp
    src/Primitives/Vector3D.cpp
    src/Materials/IMaterials.hpp
    src/Primitives/PrimitiveList.hpp
)

set_target_properties(raytracer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

target_compile_features(raytracer PRIVATE cxx_std_20)

find_package(SFML COMPONENTS graphics window audio REQUIRED)

if (NOT SFML_FOUND)
    message(FATAL_ERROR "SFML not found. Please install it.")
endif()

include_directories(${SFML_INCLUDE_DIRS} ${LIBCONFIG++_INCLUDE_DIRS})
target_link_libraries(raytracer PRIVATE 
    primitives
    sphere
    plane
    cube
    sfml-graphics 
    sfml-window 
    sfml-audio 
    ${LIBCONFIG++_LIBRARIES}
)

install(TARGETS raytracer primitives sphere plane
    RUNTIME DESTINATION bin
)
