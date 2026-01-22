/*
** EPITECH PROJECT, 2025
** Dielectric
** File description:
** Transparent / refractive material
*/
#ifndef DIELECTRIC_HPP_
#define DIELECTRIC_HPP_

#include "IMaterials.hpp"
#include <random>
#include <cmath>

namespace RayTracer {
    class Dielectric : public IMaterials {
        public:
            Dielectric(const Math::Vector3D& a, double index) : albedo(a), ir(index) {}
            ~Dielectric() = default;

            bool scatter(const Ray& r_in, const primitives::HitRecord& rec,
                         Math::Vector3D& attenuation, Ray& scattered) const override {
                attenuation = albedo;
                double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

                Math::Vector3D unit_direction = r_in.getDirection().normalized();
                double cos_theta = std::fmin((-unit_direction).dot(rec.normal), 1.0);
                double sin_theta = std::sqrt(std::max(0.0, 1.0 - cos_theta * cos_theta));

                bool cannot_refract = refraction_ratio * sin_theta > 1.0;
                Math::Vector3D direction;

                if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double()) {
                    direction = reflect(unit_direction, rec.normal);
                } else {
                    direction = refract(unit_direction, rec.normal, refraction_ratio);
                }

                scattered = Ray(rec.point, direction);
                return true;
            }

        private:
            Math::Vector3D albedo;
            double ir; // Index of refraction

            static double random_double(double min = 0.0, double max = 1.0) {
                thread_local static std::mt19937 gen(std::random_device{}());
                std::uniform_real_distribution<double> dist(min, max);
                return dist(gen);
            }

            static Math::Vector3D reflect(const Math::Vector3D& v, const Math::Vector3D& n) {
                return v - n * 2.0 * v.dot(n);
            }

            static Math::Vector3D refract(const Math::Vector3D& uv, const Math::Vector3D& n, double etai_over_etat) {
                double cos_theta = std::fmin((-uv).dot(n), 1.0);
                Math::Vector3D r_out_perp = (uv + n * cos_theta) * etai_over_etat;
                Math::Vector3D r_out_parallel = n * (-std::sqrt(std::fabs(1.0 - r_out_perp.lengthSquared())));
                return r_out_perp + r_out_parallel;
            }

            static double reflectance(double cosine, double ref_idx) {
                // Schlick's approximation
                double r0 = (1 - ref_idx) / (1 + ref_idx);
                r0 = r0 * r0;
                return r0 + (1 - r0) * std::pow(1 - cosine, 5);
            }
    };
}

#endif /* DIELECTRIC_HPP_ */
