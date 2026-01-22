/*
** EPITECH PROJECT, 2025
** Cone
** File description:
** Cone primitive
*/
#ifndef CONE_HPP_
    #define CONE_HPP_
    #include "../IPrimitive.hpp"
    #include "../Vector3D.hpp"
    #include "../../Ray.hpp"
    #include "../../Materials/IMaterials.hpp"

namespace primitives {
    class Cone : public primitives::IPrimitive {
        public:
            Cone();
            ~Cone();
            bool hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const override;
            void Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material) override;

        private:
            Math::Vector3D position;
            Math::Vector3D scale;
            RayTracer::IMaterials *material;
    };
}

#endif /* !CONE_HPP_ */
