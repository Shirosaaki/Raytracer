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
    } catch (const tools::Error &e) {
        // Sphere plugin not available
    }

    // Try to load plane plugin, but don't fail if missing
    try {
        auto planeDL = new tools::DLManager("plugins/plane.so");
        auto createPlane = (primitives::IPrimitive *(*)())planeDL->getFunction("createPlane");
        if (createPlane) {
            primitivesMap["Plane"] = createPlane;
            _dlManagers.push_back(planeDL);
        }
    } catch (const tools::Error &e) {
        // Plane plugin not available
    }

    // Try to load cube plugin, but don't fail if missing
    try {
        auto cubeDL = new tools::DLManager("plugins/cube.so");
        auto createCube = (primitives::IPrimitive *(*)())cubeDL->getFunction("createCube");
        if (createCube) {
            primitivesMap["Cube"] = createCube;
            _dlManagers.push_back(cubeDL);
        }
    } catch (const tools::Error &e) {
        // Cube plugin not available
    }
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
