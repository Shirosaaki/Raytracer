/*
** EPITECH PROJECT, 2025
** Pyramid
** File description:
** Pyramid primitive
*/
#ifndef PYRAMID_HPP_
    #define PYRAMID_HPP_
    #include "../IPrimitive.hpp"
    #include "../Vector3D.hpp"
    #include "../../Ray.hpp"
    #include "../../Materials/IMaterials.hpp"

namespace primitives {
    class Pyramid : public primitives::IPrimitive {
        public:
            Pyramid();
            ~Pyramid();
            bool hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const override;
            void Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material) override;

        private:
            Math::Vector3D position;
            Math::Vector3D scale;
            RayTracer::IMaterials *material;
    };
}

#endif /* !PYRAMID_HPP_ */
