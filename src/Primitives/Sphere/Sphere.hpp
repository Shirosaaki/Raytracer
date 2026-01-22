/*
** EPITECH PROJECT, 2025
** Sphere
** File description:
** Sphere
*/
#ifndef SPHERE_HPP_
    #define SPHERE_HPP_
    #include "../IPrimitive.hpp"
    #include "../Vector3D.hpp"
    #include "../../Ray.hpp"
    #include "../../Materials/IMaterials.hpp"

namespace primitives {
    class Sphere : public primitives::IPrimitive {
        public:
            Sphere();
            ~Sphere();
            bool hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const override;
            void Init(Math::Vector3D centre, Math::Vector3D radius, RayTracer::IMaterials *matherial) override;
            void SetRotation(Math::Vector3D rot) override { rotation = rot; }

        private:
            Math::Vector3D position = {0, 0, 0};
            double scaleX = 0, scaleY = 0, scaleZ = 0;
            Math::Vector3D rotation = {0, 0, 0};
            RayTracer::IMaterials *matherial = nullptr;
    };
}

#endif /* !SPHERE_HPP_ */
