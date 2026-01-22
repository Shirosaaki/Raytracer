/*
** EPITECH PROJECT, 2025
** Chalk
** File description:
** Matte chalk material (solid diffuse, no recursion)
*/
#ifndef CHALK_HPP_
#define CHALK_HPP_

#include "IMaterials.hpp"

namespace RayTracer {
    class Chalk : public IMaterials {
        public:
            explicit Chalk(const Math::Vector3D& a) : albedo(a) {}
            ~Chalk() = default;

            bool scatter(const Ray& /*r_in*/, const primitives::HitRecord& rec,
                         Math::Vector3D& attenuation, Ray& scattered) const override {
                attenuation = albedo;
                scattered = Ray(rec.point, Math::Vector3D(0, 0, 0));
                return false;
            }

        private:
            Math::Vector3D albedo;
    };
}

#endif /* CHALK_HPP_ */
