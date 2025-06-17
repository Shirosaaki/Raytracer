/*
** EPITECH PROJECT, 2025
** Primitive
** File description:
** Primitive
*/
#ifndef PRIMITIVE_HPP_
    #define PRIMITIVE_HPP_
    #include <iomanip>
    #include <iostream>
    #include <string>
    #include <vector>
    #include <cmath>
    #include <tuple>
    #include <map>
    #include "Vector3D.hpp"
    #include "../Ray.hpp"
    #include "../Materials/IMaterials.hpp"

namespace primitives {
    struct HitRecord {
        double t;
        Math::Vector3D point;
        Math::Vector3D normal;
        bool front_face;
        RayTracer::IMaterials *material;
        
        inline void setFaceNormal(const RayTracer::Ray& r, const Math::Vector3D& outward_normal) {
            front_face = r.getDirection().dot(outward_normal) < 0;
            normal = front_face ? outward_normal : outward_normal * (-1.0);
        }
    };

    class IPrimitive {
        public:
            ~IPrimitive() = default;
            IPrimitive() = default;
            virtual void Init(Math::Vector3D centre, Math::Vector3D radius, RayTracer::IMaterials *matherial) = 0;
            virtual bool hit(const RayTracer::Ray& r, double t_min, double t_max, primitives::HitRecord& rec) const = 0;
    };
}

#endif /* !PRIMITIVE_HPP_ */
