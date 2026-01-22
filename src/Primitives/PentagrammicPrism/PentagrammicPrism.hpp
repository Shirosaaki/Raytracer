/*
** EPITECH PROJECT, 2025
** PentagrammicPrism
** File description:
** PentagrammicPrism primitive
*/
#ifndef PENTAGRAMMIC_PRISM_HPP_
    #define PENTAGRAMMIC_PRISM_HPP_
    #include "../IPrimitive.hpp"
    #include "../Vector3D.hpp"
    #include "../../Ray.hpp"
    #include "../../Materials/IMaterials.hpp"

namespace primitives {
    class PentagrammicPrism : public primitives::IPrimitive {
        public:
            PentagrammicPrism();
            ~PentagrammicPrism();
            bool hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const override;
            void Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material) override;
            void SetRotation(Math::Vector3D rot) override { rotation = rot; }

        private:
            Math::Vector3D position;
            Math::Vector3D scale;
            Math::Vector3D rotation = {0, 0, 0};
            RayTracer::IMaterials *material;
    };
}

#endif /* !PENTAGRAMMIC_PRISM_HPP_ */
