/*
** EPITECH PROJECT, 2025
** Builder
** File description:
** Builder
*/
#ifndef BUILDER_HPP_
    #define BUILDER_HPP_
    #include <iostream>
    #include <libconfig.h++>
    #include "../tools/Error.hpp"
    #include "../tools/dlManager.hpp"
    #include "../Primitives/PrimitiveManager.hpp"
    #include "../Camera.hpp"

class Builder {
    public:
        Builder(std::string nameFile);
        ~Builder();

        void loadPrimitives();
        void loadCamera();
        void loadLights();
        void loadScene();
        void loadAll();

    private:
        libconfig::Config cfg;
        libconfig::Setting* root;
        libconfig::Setting* primitives;
        libconfig::Setting* lights;
        libconfig::Setting* camera;
        std::vector<primitives::IPrimitive *> loaded_primitives;
        RayTracer::Camera cam;
};

#endif /* !BUILDER_HPP_ */
