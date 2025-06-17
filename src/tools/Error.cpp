/*
** EPITECH PROJECT, 2025
** Error
** File description:
** Error
*/

#include "Error.hpp"

tools::Error::Error()
{
    _type = ErrorType::UNKNOWN_ERROR;
}

tools::Error::~Error()
{
}

tools::Error::Error(ErrorType type)
{
    _type = type;
}

const char *tools::Error::what() const noexcept
{
    getMessage();
    return _message.c_str();
}

void tools::Error::getMessage() const
{
    std::map<ErrorType, std::string> errorMessages = {
        {ErrorType::FILE_NOT_FOUND, "File not found"},
        {ErrorType::INVALID_FORMAT, "Invalid format"},
        {ErrorType::OUT_OF_BOUNDS, "Out of bounds"},
        {ErrorType::DIVIDED_BY_ZERO, "Divided by zero"},
        {ErrorType::INVALID_ARGUMENT, "Invalid argument"},
        {ErrorType::INVALID_OPERATION, "Invalid operation"},
        {ErrorType::MEMORY_ALLOCATION_FAILED, "Memory allocation failed"},
        {ErrorType::UNAUTHORIZED_ACCESS, "Unauthorized access"},
        {ErrorType::NETWORK_ERROR, "Network error"},
        {ErrorType::TIMEOUT, "Timeout"},
        {ErrorType::NOT_IMPLEMENTED, "Not implemented"},
        {ErrorType::INVALID_STATE, "Invalid state"},
        {ErrorType::INVALID_INDEX, "Invalid index"},
        {ErrorType::INVALID_TYPE, "Invalid type"},
        {ErrorType::INVALID_VALUE, "Invalid value"},
        {ErrorType::INVALID_KEY, "Invalid key"},
        {ErrorType::INVALID_SIZE, "Invalid size"},
        {ErrorType::INVALID_RANGE, "Invalid range"},
        {ErrorType::INVALID_POINTER, "Invalid pointer"},
        {ErrorType::INVALID_HANDLE, "Invalid handle"},
        {ErrorType::INVALID_OPERATION_CODE, "Invalid operation code"},
        {ErrorType::INVALID_PARAMETER, "Invalid parameter"},
        {ErrorType::DL_ERROR_NOT_FOUND, "Dynamic library not found"},
        {ErrorType::DL_ERROR_INVALID_FUNCTION, "Invalid function"},
        {ErrorType::DL_ERROR_INVALID_LIBRARY, "Invalid library"},
        {ErrorType::DL_ERROR_INVALID_HANDLE, "Invalid handle"}};
    auto it = errorMessages.find(_type);
    if (it != errorMessages.end())
        _message = it->second;
    else
        _message = "Unknown error";
}
