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

# -- Pyramid --

add_library(pyramid SHARED
    src/Materials/Flat.hpp
    src/Materials/Metal.hpp
    src/Primitives/Vector3D.cpp
    src/Primitives/Vector3D.hpp
    src/Materials/IMaterials.hpp
    src/Primitives/Pyramid/Pyramid.cpp
    src/Primitives/Pyramid/Pyramid.hpp
    src/Primitives/PrimitiveList.hpp
)

set_target_properties(pyramid PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/plugins"
    OUTPUT_NAME "pyramid"
    PREFIX ""
)

# -- Cone --

add_library(cone SHARED
    src/Materials/Flat.hpp
    src/Materials/Metal.hpp
    src/Primitives/Vector3D.cpp
    src/Primitives/Vector3D.hpp
    src/Materials/IMaterials.hpp
    src/Primitives/Cone/Cone.cpp
    src/Primitives/Cone/Cone.hpp
    src/Primitives/PrimitiveList.hpp
)

set_target_properties(cone PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/plugins"
    OUTPUT_NAME "cone"
    PREFIX ""
)

# -- Cylinder --

add_library(cylinder SHARED
    src/Materials/Flat.hpp
    src/Materials/Metal.hpp
    src/Primitives/Vector3D.cpp
    src/Primitives/Vector3D.hpp
    src/Materials/IMaterials.hpp
    src/Primitives/Cylinder/Cylinder.cpp
    src/Primitives/Cylinder/Cylinder.hpp
    src/Primitives/PrimitiveList.hpp
)

set_target_properties(cylinder PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/plugins"
    OUTPUT_NAME "cylinder"
    PREFIX ""
)

# -- Icosahedron --

add_library(icosahedron SHARED
    src/Materials/Flat.hpp
    src/Materials/Metal.hpp
    src/Primitives/Vector3D.cpp
    src/Primitives/Vector3D.hpp
    src/Materials/IMaterials.hpp
    src/Primitives/Icosahedron/Icosahedron.cpp
    src/Primitives/Icosahedron/Icosahedron.hpp
    src/Primitives/PrimitiveList.hpp
)

set_target_properties(icosahedron PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/plugins"
    OUTPUT_NAME "icosahedron"
    PREFIX ""
)

# -- Ellipsoid --

add_library(ellipsoid SHARED
    src/Materials/Flat.hpp
    src/Materials/Metal.hpp
    src/Primitives/Vector3D.cpp
    src/Primitives/Vector3D.hpp
    src/Materials/IMaterials.hpp
    src/Primitives/Ellipsoid/Ellipsoid.cpp
    src/Primitives/Ellipsoid/Ellipsoid.hpp
    src/Primitives/PrimitiveList.hpp
)

set_target_properties(ellipsoid PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/plugins"
    OUTPUT_NAME "ellipsoid"
    PREFIX ""
)

# -- Hemisphere --

add_library(hemisphere SHARED
    src/Materials/Flat.hpp
    src/Materials/Metal.hpp
    src/Primitives/Vector3D.cpp
    src/Primitives/Vector3D.hpp
    src/Materials/IMaterials.hpp
    src/Primitives/Hemisphere/Hemisphere.cpp
    src/Primitives/Hemisphere/Hemisphere.hpp
    src/Primitives/PrimitiveList.hpp
)

set_target_properties(hemisphere PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/plugins"
    OUTPUT_NAME "hemisphere"
    PREFIX ""
)

# -- Dodecahedron --

add_library(dodecahedron SHARED
    src/Materials/Flat.hpp
    src/Materials/Metal.hpp
    src/Primitives/Vector3D.cpp
    src/Primitives/Vector3D.hpp
    src/Materials/IMaterials.hpp
    src/Primitives/Dodecahedron/Dodecahedron.cpp
    src/Primitives/Dodecahedron/Dodecahedron.hpp
    src/Primitives/PrimitiveList.hpp
)

set_target_properties(dodecahedron PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/plugins"
    OUTPUT_NAME "dodecahedron"
    PREFIX ""
)

# -- TriangularPrism --

add_library(triangularprism SHARED
    src/Materials/Flat.hpp
    src/Materials/Metal.hpp
    src/Primitives/Vector3D.cpp
    src/Primitives/Vector3D.hpp
    src/Materials/IMaterials.hpp
    src/Primitives/TriangularPrism/TriangularPrism.cpp
    src/Primitives/TriangularPrism/TriangularPrism.hpp
    src/Primitives/PrimitiveList.hpp
)

set_target_properties(triangularprism PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/plugins"
    OUTPUT_NAME "triangularprism"
    PREFIX ""
)

# -- Torus --

add_library(torus SHARED
    src/Materials/Flat.hpp
    src/Materials/Metal.hpp
    src/Primitives/Vector3D.cpp
    src/Primitives/Vector3D.hpp
    src/Materials/IMaterials.hpp
    src/Primitives/Torus/Torus.cpp
    src/Primitives/Torus/Torus.hpp
    src/Primitives/PrimitiveList.hpp
)

set_target_properties(torus PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/plugins"
    OUTPUT_NAME "torus"
    PREFIX ""
)

# -- Tetrahedron --

add_library(tetrahedron SHARED
    src/Materials/Flat.hpp
    src/Materials/Metal.hpp
    src/Primitives/Vector3D.cpp
    src/Primitives/Vector3D.hpp
    src/Materials/IMaterials.hpp
    src/Primitives/Tetrahedron/Tetrahedron.cpp
    src/Primitives/Tetrahedron/Tetrahedron.hpp
    src/Primitives/PrimitiveList.hpp
)

set_target_properties(tetrahedron PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/plugins"
    OUTPUT_NAME "tetrahedron"
    PREFIX ""
)

# -- Octahedron --

add_library(octahedron SHARED
    src/Materials/Flat.hpp
    src/Materials/Metal.hpp
    src/Primitives/Vector3D.cpp
    src/Primitives/Vector3D.hpp
    src/Materials/IMaterials.hpp
    src/Primitives/Octahedron/Octahedron.cpp
    src/Primitives/Octahedron/Octahedron.hpp
    src/Primitives/PrimitiveList.hpp
)

set_target_properties(octahedron PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/plugins"
    OUTPUT_NAME "octahedron"
    PREFIX ""
)

# -- PentagrammicPrism --

add_library(pentagrammicprism SHARED
    src/Materials/Flat.hpp
    src/Materials/Metal.hpp
    src/Primitives/Vector3D.cpp
    src/Primitives/Vector3D.hpp
    src/Materials/IMaterials.hpp
    src/Primitives/PentagrammicPrism/PentagrammicPrism.cpp
    src/Primitives/PentagrammicPrism/PentagrammicPrism.hpp
    src/Primitives/PrimitiveList.hpp
)

set_target_properties(pentagrammicprism PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/plugins"
    OUTPUT_NAME "pentagrammicprism"
    PREFIX ""
)

# -- HexagonalPyramid --

add_library(hexagonalpyramid SHARED
    src/Materials/Flat.hpp
    src/Materials/Metal.hpp
    src/Primitives/Vector3D.cpp
    src/Primitives/Vector3D.hpp
    src/Materials/IMaterials.hpp
    src/Primitives/HexagonalPyramid/HexagonalPyramid.cpp
    src/Primitives/HexagonalPyramid/HexagonalPyramid.hpp
    src/Primitives/PrimitiveList.hpp
)

set_target_properties(hexagonalpyramid PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/plugins"
    OUTPUT_NAME "hexagonalpyramid"
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
    pyramid
    cone
    cylinder
    icosahedron
    ellipsoid
    hemisphere
    dodecahedron
    triangularprism
    torus
    tetrahedron
    octahedron
    pentagrammicprism
    hexagonalpyramid
    sfml-graphics 
    sfml-window 
    sfml-audio 
    ${LIBCONFIG++_LIBRARIES}
)

install(TARGETS raytracer primitives sphere plane
    RUNTIME DESTINATION bin
)
