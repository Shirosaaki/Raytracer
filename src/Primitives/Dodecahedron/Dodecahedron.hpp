/*
** EPITECH PROJECT, 2025
** Dodecahedron
** File description:
** Dodecahedron primitive
*/
#ifndef DODECAHEDRON_HPP_
    #define DODECAHEDRON_HPP_
    #include "../IPrimitive.hpp"
    #include "../Vector3D.hpp"
    #include "../../Ray.hpp"
    #include "../../Materials/IMaterials.hpp"

namespace primitives {
    class Dodecahedron : public primitives::IPrimitive {
        public:
            Dodecahedron();
            ~Dodecahedron();
            bool hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const override;
            void Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material) override;

        private:
            Math::Vector3D position;
            double radius;
            RayTracer::IMaterials *material;
    };
}

#endif /* !DODECAHEDRON_HPP_ */
