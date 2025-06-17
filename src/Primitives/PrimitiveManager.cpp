/*
** EPITECH PROJECT, 2025
** PRIMITIVE_MANAGER
** File description:
** PRIMITIVE_MANAGER
*/
#include "PrimitiveManager.hpp"

primitives::PrimitiveManager::PrimitiveManager()
{
    auto sphereDL = new tools::DLManager("plugins/sphere.so");
    if (!sphereDL->getLibrary())
        throw tools::Error(tools::Error::ErrorType::DL_ERROR_INVALID_LIBRARY);
    auto createSphere = (primitives::IPrimitive *(*)())sphereDL->getFunction("createSphere");
    if (!createSphere)
        throw tools::Error(tools::Error::ErrorType::DL_ERROR_INVALID_FUNCTION);
    primitivesMap["Sphere"] = createSphere;
    _dlManagers.push_back(sphereDL);

    auto planeDL = new tools::DLManager("plugins/plane.so");
    if (!planeDL->getLibrary())
        throw tools::Error(tools::Error::ErrorType::DL_ERROR_INVALID_LIBRARY);
    auto createPlane = (primitives::IPrimitive *(*)())planeDL->getFunction("createPlane");
    if (!createPlane)
        throw tools::Error(tools::Error::ErrorType::DL_ERROR_INVALID_FUNCTION);
    primitivesMap["Plane"] = createPlane;
    _dlManagers.push_back(planeDL);
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
    throw std::runtime_error("Primitive not found");
    return nullptr;
}

extern "C" primitives::PrimitiveManager *createPrimitiveManager()
{
    return new primitives::PrimitiveManager();
}
