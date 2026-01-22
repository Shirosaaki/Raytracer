/*
** EPITECH PROJECT, 2025
** Octahedron
** File description:
** Octahedron primitive
*/
#ifndef OCTAHEDRON_HPP_
    #define OCTAHEDRON_HPP_
    #include "../IPrimitive.hpp"
    #include "../Vector3D.hpp"
    #include "../../Ray.hpp"
    #include "../../Materials/IMaterials.hpp"

namespace primitives {
    class Octahedron : public primitives::IPrimitive {
        public:
            Octahedron();
            ~Octahedron();
            bool hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const override;
            void Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material) override;

        private:
            Math::Vector3D position;
            double radius;
            RayTracer::IMaterials *material;
    };
}

#endif /* !OCTAHEDRON_HPP_ */
