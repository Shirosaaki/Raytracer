/*
** EPITECH PROJECT, 2025
** Flat
** File description:
** Flat
*/
#ifndef FLAT_HPP_
    #define FLAT_HPP_
    #include "IMaterials.hpp"

namespace RayTracer {
    class Flat : public IMaterials {
        public:
            Flat(const Math::Vector3D& a) : albedo(a) {}
            ~Flat() {}
            
            bool scatter(const Ray& r_in, const primitives::HitRecord& rec, 
                Math::Vector3D& attenuation, Ray& scattered) const override {
                attenuation = albedo;
                return false;
            }
            
            Math::Vector3D albedo;
    };
}

#endif /* !FLAT_HPP_ */
