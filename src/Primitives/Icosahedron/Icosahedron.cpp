/*
** EPITECH PROJECT, 2025
** Icosahedron
** File description:
** Icosahedron primitive
*/
#include "Icosahedron.hpp"
#include <cmath>

primitives::Icosahedron::Icosahedron() 
    : position(0, 0, 0), radius(1), material(nullptr)
{
}

primitives::Icosahedron::~Icosahedron() 
{
}

bool primitives::Icosahedron::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    // Approximate icosahedron as a sphere for ray tracing
    Math::Vector3D oc = r.getOrigin() - position;
    double a = r.getDirection().dot(r.getDirection());
    double b = oc.dot(r.getDirection());
    double c = oc.dot(oc) - radius * radius;
    double discriminant = b * b - a * c;
    
    if (discriminant > 0) {
        double t = (-b - std::sqrt(discriminant)) / a;
        if (t > t_min && t < t_max) {
            rec.t = t;
            rec.point = r.at(t);
            rec.normal = (rec.point - position) / radius;
            rec.setFaceNormal(r, rec.normal);
            rec.material = material;
            return true;
        }
    }
    
    return false;
}

void primitives::Icosahedron::Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material)
{
    this->position = centre;
    this->radius = scale.x;
    this->material = material;
}

extern "C" primitives::IPrimitive *createIcosahedron()
{
    return new primitives::Icosahedron();
}
