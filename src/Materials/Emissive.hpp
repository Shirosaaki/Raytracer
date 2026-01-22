/*
** EPITECH PROJECT, 2025
** Emissive
** File description:
** Simple emissive material (always returns its emission color)
*/
#ifndef EMISSIVE_HPP_
#define EMISSIVE_HPP_

#include "IMaterials.hpp"

namespace RayTracer {
    class Emissive : public IMaterials {
        public:
            explicit Emissive(const Math::Vector3D& emit, double strength = 1.0)
            : emission(emit), intensity(strength) {}
            ~Emissive() = default;

            bool scatter(const Ray& /*r_in*/, const primitives::HitRecord& rec,
                         Math::Vector3D& attenuation, Ray& scattered) const override {
                // No scattering; just emit the color and terminate the ray
                attenuation = emission * intensity;
                // Set a dummy scattered ray to satisfy interface (unused by caller when returns false)
                scattered = Ray(rec.point, Math::Vector3D(0, 0, 0));
                return false;
            }

        private:
            Math::Vector3D emission;
            double intensity;
    };
}

#endif /* EMISSIVE_HPP_ */
