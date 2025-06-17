/*
** EPITECH PROJECT, 2025
** Metal
** File description:
** Metal
*/
#ifndef METAL_HPP_
    #define METAL_HPP_
    #include "IMaterials.hpp"

namespace RayTracer {
    class Metal : public IMaterials {
        public:
            Metal(const Math::Vector3D& a, double f = 0.0) : albedo(a), fuzz(f < 1 ? f : 1) {}
            
            bool scatter(const Ray& r_in, const primitives::HitRecord& rec, 
                Math::Vector3D& attenuation, Ray& scattered) const override {
                Math::Vector3D reflected = reflect(r_in.getDirection().normalized(), rec.normal);
                scattered = Ray(rec.point, reflected + random_in_unit_sphere() * fuzz);
                attenuation = albedo;
                return (scattered.getDirection().dot(rec.normal) > 0);
            }
            
            Math::Vector3D reflect(const Math::Vector3D& v, const Math::Vector3D& n) const {
                return v - n * 2.0 * v.dot(n);
            }
            
            Math::Vector3D albedo;
            double fuzz;
    };
}

#endif /* !METAL_HPP_ */
