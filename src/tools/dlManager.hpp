/*
** EPITECH PROJECT, 2025
** dlManager
** File description:
** dlManager
*/
#ifndef DL_MANAGER_HPP_
    #define DL_MANAGER_HPP_
    #include <dlfcn.h>
    #include <iostream>
    #include <string>
    #include <vector>
    #include <map>
    #include "Error.hpp"

namespace tools {
    class DLManager {
        public:
            DLManager(const std::string &path);
            ~DLManager();
            void *getFunction(const std::string &name);
            void *getLibrary() const;
            void loadNewLibrary(const std::string &path);
            void closeLibrary();

        private:
            void *_handle;
            void *_function;
            std::vector<void *> _libraries;
            std::vector<void *> _functions;
    };
}


#endif /* !DL_MANAGER_HPP_ */
