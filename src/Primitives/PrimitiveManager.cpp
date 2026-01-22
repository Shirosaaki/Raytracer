/*
** EPITECH PROJECT, 2025
** PRIMITIVE_MANAGER
** File description:
** PRIMITIVE_MANAGER
*/
#include "PrimitiveManager.hpp"

primitives::PrimitiveManager::PrimitiveManager()
{
    // Try to load sphere plugin, but don't fail if missing
    try {
        auto sphereDL = new tools::DLManager("plugins/sphere.so");
        auto createSphere = (primitives::IPrimitive *(*)())sphereDL->getFunction("createSphere");
        if (createSphere) {
            primitivesMap["Sphere"] = createSphere;
            _dlManagers.push_back(sphereDL);
        }
    } catch (const tools::Error &e) {}

    // Try to load plane plugin, but don't fail if missing
    try {
        auto planeDL = new tools::DLManager("plugins/plane.so");
        auto createPlane = (primitives::IPrimitive *(*)())planeDL->getFunction("createPlane");
        if (createPlane) {
            primitivesMap["Plane"] = createPlane;
            _dlManagers.push_back(planeDL);
        }
    } catch (const tools::Error &e) {}

    // Try to load cube plugin, but don't fail if missing
    try {
        auto cubeDL = new tools::DLManager("plugins/cube.so");
        auto createCube = (primitives::IPrimitive *(*)())cubeDL->getFunction("createCube");
        if (createCube) {
            primitivesMap["Cube"] = createCube;
            _dlManagers.push_back(cubeDL);
        }
    } catch (const tools::Error &e) {}

    // Try to load pyramid plugin
    try {
        auto pyramidDL = new tools::DLManager("plugins/pyramid.so");
        auto createPyramid = (primitives::IPrimitive *(*)())pyramidDL->getFunction("createPyramid");
        if (createPyramid) {
            primitivesMap["Pyramid"] = createPyramid;
            _dlManagers.push_back(pyramidDL);
        }
    } catch (const tools::Error &e) {}

    // Try to load cone plugin
    try {
        auto coneDL = new tools::DLManager("plugins/cone.so");
        auto createCone = (primitives::IPrimitive *(*)())coneDL->getFunction("createCone");
        if (createCone) {
            primitivesMap["Cone"] = createCone;
            _dlManagers.push_back(coneDL);
        }
    } catch (const tools::Error &e) {}

    // Try to load cylinder plugin
    try {
        auto cylinderDL = new tools::DLManager("plugins/cylinder.so");
        auto createCylinder = (primitives::IPrimitive *(*)())cylinderDL->getFunction("createCylinder");
        if (createCylinder) {
            primitivesMap["Cylinder"] = createCylinder;
            _dlManagers.push_back(cylinderDL);
        }
    } catch (const tools::Error &e) {}

    // Try to load icosahedron plugin
    try {
        auto icosahedronDL = new tools::DLManager("plugins/icosahedron.so");
        auto createIcosahedron = (primitives::IPrimitive *(*)())icosahedronDL->getFunction("createIcosahedron");
        if (createIcosahedron) {
            primitivesMap["Icosahedron"] = createIcosahedron;
            _dlManagers.push_back(icosahedronDL);
        }
    } catch (const tools::Error &e) {}

    // Try to load ellipsoid plugin
    try {
        auto ellipsoidDL = new tools::DLManager("plugins/ellipsoid.so");
        auto createEllipsoid = (primitives::IPrimitive *(*)())ellipsoidDL->getFunction("createEllipsoid");
        if (createEllipsoid) {
            primitivesMap["Ellipsoid"] = createEllipsoid;
            _dlManagers.push_back(ellipsoidDL);
        }
    } catch (const tools::Error &e) {}

    // Try to load hemisphere plugin
    try {
        auto hemisphereDL = new tools::DLManager("plugins/hemisphere.so");
        auto createHemisphere = (primitives::IPrimitive *(*)())hemisphereDL->getFunction("createHemisphere");
        if (createHemisphere) {
            primitivesMap["Hemisphere"] = createHemisphere;
            _dlManagers.push_back(hemisphereDL);
        }
    } catch (const tools::Error &e) {}

    // Try to load dodecahedron plugin
    try {
        auto dodecahedronDL = new tools::DLManager("plugins/dodecahedron.so");
        auto createDodecahedron = (primitives::IPrimitive *(*)())dodecahedronDL->getFunction("createDodecahedron");
        if (createDodecahedron) {
            primitivesMap["Dodecahedron"] = createDodecahedron;
            _dlManagers.push_back(dodecahedronDL);
        }
    } catch (const tools::Error &e) {}

    // Try to load triangular prism plugin
    try {
        auto triangularPrismDL = new tools::DLManager("plugins/triangularprism.so");
        auto createTriangularPrism = (primitives::IPrimitive *(*)())triangularPrismDL->getFunction("createTriangularPrism");
        if (createTriangularPrism) {
            primitivesMap["TriangularPrism"] = createTriangularPrism;
            _dlManagers.push_back(triangularPrismDL);
        }
    } catch (const tools::Error &e) {}

    // Try to load torus plugin
    try {
        auto torusDL = new tools::DLManager("plugins/torus.so");
        auto createTorus = (primitives::IPrimitive *(*)())torusDL->getFunction("createTorus");
        if (createTorus) {
            primitivesMap["Torus"] = createTorus;
            _dlManagers.push_back(torusDL);
        }
    } catch (const tools::Error &e) {}

    // Try to load tetrahedron plugin
    try {
        auto tetrahedronDL = new tools::DLManager("plugins/tetrahedron.so");
        auto createTetrahedron = (primitives::IPrimitive *(*)())tetrahedronDL->getFunction("createTetrahedron");
        if (createTetrahedron) {
            primitivesMap["Tetrahedron"] = createTetrahedron;
            _dlManagers.push_back(tetrahedronDL);
        }
    } catch (const tools::Error &e) {}

    // Try to load octahedron plugin
    try {
        auto octahedronDL = new tools::DLManager("plugins/octahedron.so");
        auto createOctahedron = (primitives::IPrimitive *(*)())octahedronDL->getFunction("createOctahedron");
        if (createOctahedron) {
            primitivesMap["Octahedron"] = createOctahedron;
            _dlManagers.push_back(octahedronDL);
        }
    } catch (const tools::Error &e) {}

    // Try to load pentagrammic prism plugin
    try {
        auto pentagrammicPrismDL = new tools::DLManager("plugins/pentagrammicprism.so");
        auto createPentagrammicPrism = (primitives::IPrimitive *(*)())pentagrammicPrismDL->getFunction("createPentagrammicPrism");
        if (createPentagrammicPrism) {
            primitivesMap["PentagrammicPrism"] = createPentagrammicPrism;
            _dlManagers.push_back(pentagrammicPrismDL);
        }
    } catch (const tools::Error &e) {}

    // Try to load hexagonal pyramid plugin
    try {
        auto hexagonalPyramidDL = new tools::DLManager("plugins/hexagonalpyramid.so");
        auto createHexagonalPyramid = (primitives::IPrimitive *(*)())hexagonalPyramidDL->getFunction("createHexagonalPyramid");
        if (createHexagonalPyramid) {
            primitivesMap["HexagonalPyramid"] = createHexagonalPyramid;
            _dlManagers.push_back(hexagonalPyramidDL);
        }
    } catch (const tools::Error &e) {}
}

primitives::PrimitiveManager::~PrimitiveManager()
{
    for (auto &dl : _dlManagers) {
        if (dl) {
            dl->closeLibrary();
            delete dl;
        }
    }
    delete _dlManager;
    _dlManager = nullptr;
    primitivesMap.clear();
}

primitives::IPrimitive *primitives::PrimitiveManager::createPrimitive(const std::string& name)
{
    auto it = primitivesMap.find(name);
    if (it != primitivesMap.end())
        return it->second();
    throw std::runtime_error("Primitive type '" + name + "' not available - check if the corresponding plugin is installed");
    return nullptr;
}

extern "C" primitives::PrimitiveManager *createPrimitiveManager()
{
    return new primitives::PrimitiveManager();
}
