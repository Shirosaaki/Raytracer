/*
** EPITECH PROJECT, 2025
** PrimitiveManager
** File description:
** PrimitiveManager
*/
#ifndef PRIMITIVE_MANAGER_HPP_
    #define PRIMITIVE_MANAGER_HPP_
    #include "IPrimitive.hpp"
    #include "../tools/dlManager.hpp"
    #include "../tools/Error.hpp"
    #include <map>
    #include <string>


namespace primitives {
    class PrimitiveManager {
        public:
            PrimitiveManager();
            ~PrimitiveManager();
            primitives::IPrimitive *createPrimitive(const std::string &name);

        private:
            std::map<std::string, primitives::IPrimitive *(*)()> primitivesMap;
            tools::DLManager *_dlManager;
            std::vector<tools::DLManager *> _dlManagers;
    };
}
#endif /* !PRIMITIVE_MANAGER_HPP_ */
