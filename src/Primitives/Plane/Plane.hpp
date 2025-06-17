/*
** EPITECH PROJECT, 2025
** Plane
** File description:
** Plane
*/
#ifndef PLANE_HPP_
    #define PLANE_HPP_
    #include "../IPrimitive.hpp"
    #include "../Vector3D.hpp"

namespace primitives {
    class Plane : public primitives::IPrimitive {
        public:
            Plane();
            ~Plane();
            void Init(Math::Vector3D centre, Math::Vector3D radius, RayTracer::IMaterials *matherial) override;
            bool hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const override;
        
        private:
            Math::Vector3D position = {0, 0, 0};
            Math::Vector3D rotation = {0, 0, 0};
            Math::Vector3D axis = {0, 0, 0};
            RayTracer::IMaterials *matherial = nullptr;
    };
}

#endif /* !PLANE_HPP_ */
