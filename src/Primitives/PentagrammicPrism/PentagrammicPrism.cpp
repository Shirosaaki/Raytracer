/*
** EPITECH PROJECT, 2025
** PentagrammicPrism
** File description:
** PentagrammicPrism primitive
*/
#include "PentagrammicPrism.hpp"
#include <cmath>

primitives::PentagrammicPrism::PentagrammicPrism() 
    : position(0, 0, 0), scale(1, 1, 1), material(nullptr)
{
}

primitives::PentagrammicPrism::~PentagrammicPrism() 
{
}

bool primitives::PentagrammicPrism::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    // Simplified pentagrammic prism using cylinder approximation
    Math::Vector3D oc = r.getOrigin() - position;
    Math::Vector3D dir = r.getDirection();
    
    double a = dir.x * dir.x + dir.y * dir.y;
    double b = 2 * (oc.x * dir.x + oc.y * dir.y);
    double c = oc.x * oc.x + oc.y * oc.y - (scale.x * scale.x);
    
    double discriminant = b * b - 4 * a * c;
    if (discriminant >= 0 && std::abs(a) > 1e-6) {
        double t = (-b - std::sqrt(discriminant)) / (2 * a);
        if (t > t_min && t < t_max) {
            rec.t = t;
            rec.point = r.at(t);
            Math::Vector3D normal = rec.point - position;
            normal.z = 0;
            rec.normal = normal.normalized();
            rec.setFaceNormal(r, rec.normal);
            rec.material = material;
            return true;
        }
    }
    
    return false;
}

void primitives::PentagrammicPrism::Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material)
{
    this->position = centre;
    this->scale = scale;
    this->material = material;
}

extern "C" primitives::IPrimitive *createPentagrammicPrism()
{
    return new primitives::PentagrammicPrism();
}
