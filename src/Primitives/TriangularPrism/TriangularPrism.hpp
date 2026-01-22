/*
** EPITECH PROJECT, 2025
** TriangularPrism
** File description:
** TriangularPrism primitive
*/
#ifndef TRIANGULAR_PRISM_HPP_
    #define TRIANGULAR_PRISM_HPP_
    #include "../IPrimitive.hpp"
    #include "../Vector3D.hpp"
    #include "../../Ray.hpp"
    #include "../../Materials/IMaterials.hpp"

namespace primitives {
    class TriangularPrism : public primitives::IPrimitive {
        public:
            TriangularPrism();
            ~TriangularPrism();
            bool hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const override;
            void Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material) override;

        private:
            Math::Vector3D position;
            Math::Vector3D scale;
            RayTracer::IMaterials *material;
    };
}

#endif /* !TRIANGULAR_PRISM_HPP_ */
