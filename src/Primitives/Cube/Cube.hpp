/*
** EPITECH PROJECT, 2025
** cube
** File description:
** cube
*/
#ifndef CUBE_HPP_
    #define CUBE_HPP_
    #include "../IPrimitive.hpp"

namespace primitives {
    class Cube : public primitives::IPrimitive {
        public:
            Cube();
            ~Cube();
            bool hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const override;
            void Init(Math::Vector3D centre, Math::Vector3D radius, RayTracer::IMaterials *matherial) override;

        private:
            Math::Vector3D position = {0, 0, 0};
            Math::Vector3D rotation = {0, 0, 0};
            Math::Vector3D axis = {0, 0, 0};
            RayTracer::IMaterials *matherial = nullptr;
    };
}

#endif /* !CUBE_HPP_ */
