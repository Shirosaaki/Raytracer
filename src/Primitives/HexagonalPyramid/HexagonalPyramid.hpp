/*
** EPITECH PROJECT, 2025
** HexagonalPyramid
** File description:
** HexagonalPyramid primitive
*/
#ifndef HEXAGONAL_PYRAMID_HPP_
    #define HEXAGONAL_PYRAMID_HPP_
    #include "../IPrimitive.hpp"
    #include "../Vector3D.hpp"
    #include "../../Ray.hpp"
    #include "../../Materials/IMaterials.hpp"

namespace primitives {
    class HexagonalPyramid : public primitives::IPrimitive {
        public:
            HexagonalPyramid();
            ~HexagonalPyramid();
            bool hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const override;
            void Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material) override;

        private:
            Math::Vector3D position;
            Math::Vector3D scale;
            RayTracer::IMaterials *material;
    };
}

#endif /* !HEXAGONAL_PYRAMID_HPP_ */
