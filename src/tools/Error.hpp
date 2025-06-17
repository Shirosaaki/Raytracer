/*
** EPITECH PROJECT, 2025
** Error
** File description:
** Error
*/
#ifndef ERROR_HPP_
    #define ERROR_HPP_
    #include <iostream>
    #include <string>
    #include <exception>
    #include <stdexcept>
    #include <cstdlib>
    #include <map>

namespace tools {
    class Error : public std::exception {
        public:
            enum class ErrorType {
                FILE_NOT_FOUND,
                INVALID_FORMAT,
                OUT_OF_BOUNDS,
                DIVIDED_BY_ZERO,
                INVALID_ARGUMENT,
                INVALID_OPERATION,
                MEMORY_ALLOCATION_FAILED,
                UNAUTHORIZED_ACCESS,
                NETWORK_ERROR,
                TIMEOUT,
                NOT_IMPLEMENTED,
                INVALID_STATE,
                INVALID_INDEX,
                INVALID_TYPE,
                INVALID_VALUE,
                INVALID_KEY,
                INVALID_SIZE,
                INVALID_RANGE,
                INVALID_POINTER,
                INVALID_HANDLE,
                INVALID_OPERATION_CODE,
                INVALID_PARAMETER,
                DL_ERROR_NOT_FOUND,
                DL_ERROR_INVALID_FUNCTION,
                DL_ERROR_INVALID_LIBRARY,
                DL_ERROR_INVALID_HANDLE,
                UNKNOWN_ERROR
            };
            Error();
            ~Error();
            Error(ErrorType type);
            const char *what() const noexcept override;
            void getMessage() const;
            ErrorType getType() const;

        private:
            mutable std::string _message;
            ErrorType _type;
    };
}

#endif /* !ERROR_HPP_ */
