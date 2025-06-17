/*
** EPITECH PROJECT, 2025
** dlManager
** File description:
** dlManager
*/
#include "dlManager.hpp"

tools::DLManager::DLManager(const std::string &path)
{
    _handle = dlopen(path.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    if (!_handle)
        throw tools::Error(tools::Error::ErrorType::DL_ERROR_INVALID_LIBRARY);
    _libraries.push_back(_handle);
    _function = nullptr;
}

tools::DLManager::~DLManager()
{
    closeLibrary();
}

void *tools::DLManager::getFunction(const std::string &name)
{
    _function = dlsym(_handle, name.c_str());
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        throw tools::Error(tools::Error::ErrorType::DL_ERROR_INVALID_FUNCTION);
    }
    if (!_function)
        throw tools::Error(tools::Error::ErrorType::DL_ERROR_INVALID_FUNCTION);
    _functions.push_back(_function);
    return _function;
}

void *tools::DLManager::getLibrary() const
{
    return _handle;
}

void tools::DLManager::loadNewLibrary(const std::string &path)
{
    closeLibrary();
    _handle = dlopen(path.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    if (!_handle)
        throw tools::Error(tools::Error::ErrorType::DL_ERROR_INVALID_LIBRARY);
    _libraries.push_back(_handle);
}

void tools::DLManager::closeLibrary()
{
    try {
        for (auto &lib : _libraries) {
            if (lib) {
                dlclose(lib);
            }
        }
        _libraries.clear();
        if (_handle) {
            dlclose(_handle);
            _handle = nullptr;
        }
    } catch (const std::exception &e) {
        throw tools::Error(tools::Error::ErrorType::DL_ERROR_INVALID_HANDLE);
    }
}
