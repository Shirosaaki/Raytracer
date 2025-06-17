/*
** EPITECH PROJECT, 2025
** RaytracerByLauric
** File description:
** hitable_list
*/

#ifndef PRIMITIVES_LIST_HPP_
    #define PRIMITIVES_LIST_HPP_
    #include "IPrimitive.hpp"
    #include "../Ray.hpp"
    #include <vector>

namespace primitives {
    struct HitRecord;
    class PrimitivesList : public primitives::IPrimitive {
        public:
            PrimitivesList() : list_size(0) {}
            PrimitivesList(IPrimitive **l, int n) : list_size(n) {
                for (int i = 0; i < n; i++)
                    list.push_back(l[i]);
            }
            ~PrimitivesList() {
                for (auto& item : list) {
                    delete item;
                }
            }
            void Init(Math::Vector3D centre, Math::Vector3D radius, RayTracer::IMaterials *matherial) override {
            }
            bool hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord& rec) const override;
            void add(IPrimitive *h) {
                list.push_back(h);
                list_size++;
            }
            std::vector<IPrimitive *> list;
            int list_size;
    };

    bool primitives::PrimitivesList::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord& rec) const {
        HitRecord temp_rec;
        bool hit_anything = false;
        double closest_so_far = t_max;
    
        for (const auto& item : list) {
            if (item->hit(r, t_min, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
                return true;
            }
        }
        return hit_anything;
    }
}


#endif