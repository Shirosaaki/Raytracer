/*
** EPITECH PROJECT, 2025
** Tetrahedron
** File description:
** Tetrahedron primitive
*/
#ifndef TETRAHEDRON_HPP_
    #define TETRAHEDRON_HPP_
    #include "../IPrimitive.hpp"
    #include "../Vector3D.hpp"
    #include "../../Ray.hpp"
    #include "../../Materials/IMaterials.hpp"

namespace primitives {
    class Tetrahedron : public primitives::IPrimitive {
        public:
            Tetrahedron();
            ~Tetrahedron();
            bool hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const override;
            void Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material) override;

        private:
            Math::Vector3D position;
            double radius;
            RayTracer::IMaterials *material;
    };
}

#endif /* !TETRAHEDRON_HPP_ */
