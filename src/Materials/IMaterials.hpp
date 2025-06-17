/*
** EPITECH PROJECT, 2025
** IMAT
** File description:
** IMAT
*/
#ifndef IMATERIAL_HPP_
    #define IMATERIAL_HPP_
    #include "../Ray.hpp"
    #include <random>

namespace primitives {
    struct HitRecord;
}

namespace RayTracer {
    
    inline Math::Vector3D random_in_unit_sphere() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<double> dist(-1.0, 1.0);
        
        Math::Vector3D p;
        double len_squared;
        do {
            p = Math::Vector3D(dist(gen), dist(gen), dist(gen));
            len_squared = p.dot(p);
        } while (len_squared >= 1.0);
        
        return p;
    }

    class IMaterials {
        public:
            ~IMaterials() = default;
            virtual bool scatter(const Ray& r_in, const primitives::HitRecord& rec, 
                Math::Vector3D& attenuation, Ray& scattered) const = 0;
    };
}

#endif /* !IMATERIAL_HPP_ */
