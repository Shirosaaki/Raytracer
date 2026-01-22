/*
** EPITECH PROJECT, 2025
** Torus
** File description:
** Torus primitive
*/
#ifndef TORUS_HPP_
    #define TORUS_HPP_
    #include "../IPrimitive.hpp"
    #include "../Vector3D.hpp"
    #include "../../Ray.hpp"
    #include "../../Materials/IMaterials.hpp"

namespace primitives {
    class Torus : public primitives::IPrimitive {
        public:
            Torus();
            ~Torus();
            bool hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const override;
            void Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material) override;
            void SetRotation(Math::Vector3D rot) override { rotation = rot; }

        private:
            Math::Vector3D position;
            double majorRadius;
            double minorRadius;
            Math::Vector3D rotation = {0, 0, 0};
            RayTracer::IMaterials *material;
    };
}

#endif /* !TORUS_HPP_ */
