/*
** EPITECH PROJECT, 2025
** Dodecahedron
** File description:
** Dodecahedron primitive
*/
#include "Dodecahedron.hpp"
#include <cmath>

primitives::Dodecahedron::Dodecahedron() 
    : position(0, 0, 0), radius(1), material(nullptr)
{
}

primitives::Dodecahedron::~Dodecahedron() 
{
}

bool primitives::Dodecahedron::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    // Approximate dodecahedron as sphere for ray tracing
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

void primitives::Dodecahedron::Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material)
{
    this->position = centre;
    this->radius = scale.x;
    this->material = material;
}

extern "C" primitives::IPrimitive *createDodecahedron()
{
    return new primitives::Dodecahedron();
}
