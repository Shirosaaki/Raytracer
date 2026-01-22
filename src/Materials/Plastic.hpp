/*
** EPITECH PROJECT, 2025
** Plastic
** File description:
** Plastic material: mostly diffuse with a light glossy reflection
*/
#ifndef PLASTIC_HPP_
#define PLASTIC_HPP_

#include "IMaterials.hpp"
#include <random>
#include <cmath>

namespace RayTracer {
    class Plastic : public IMaterials {
        public:
            Plastic(const Math::Vector3D& a, double gloss = 0.1)
            : albedo(a), glossiness(gloss < 1.0 ? gloss : 1.0) {}

            bool scatter(const Ray& r_in, const primitives::HitRecord& rec,
                         Math::Vector3D& attenuation, Ray& scattered) const override {
                // Blend between a glossy reflection and a solid diffuse response
                double spec_chance = 0.25; // 25% glossy, 75% diffuse
                double roll = random_double();

                if (roll < spec_chance) {
                    // Glossy reflection (keeps recursive bounce)
                    attenuation = albedo;
                    Math::Vector3D reflected = reflect(r_in.getDirection().normalized(), rec.normal);
                    scattered = Ray(rec.point, reflected + random_in_unit_sphere() * glossiness);
                    return (scattered.getDirection().dot(rec.normal) > 0);
                }

                // Diffuse: return the base color directly (no recursion) to avoid overly dark results
                attenuation = albedo;
                scattered = Ray(rec.point, Math::Vector3D(0, 0, 0));
                return false;
            }

        private:
            Math::Vector3D albedo;
            double glossiness;

            static double random_double(double min = 0.0, double max = 1.0) {
                thread_local static std::mt19937 gen(std::random_device{}());
                std::uniform_real_distribution<double> dist(min, max);
                return dist(gen);
            }

            static Math::Vector3D reflect(const Math::Vector3D& v, const Math::Vector3D& n) {
                return v - n * 2.0 * v.dot(n);
            }
    };
}

#endif /* PLASTIC_HPP_ */
