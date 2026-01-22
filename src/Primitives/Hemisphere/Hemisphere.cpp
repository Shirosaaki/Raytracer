/*
** EPITECH PROJECT, 2025
** Hemisphere
** File description:
** Hemisphere primitive
*/
#include "Hemisphere.hpp"
#include <cmath>

primitives::Hemisphere::Hemisphere() 
    : position(0, 0, 0), radius(1), material(nullptr)
{
}

primitives::Hemisphere::~Hemisphere() 
{
}

bool primitives::Hemisphere::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    // Hemisphere hit detection (upper half of sphere)
    Math::Vector3D oc = r.getOrigin() - position;
    double a = r.getDirection().dot(r.getDirection());
    double b = oc.dot(r.getDirection());
    double c = oc.dot(oc) - radius * radius;
    double discriminant = b * b - a * c;
    
    if (discriminant > 0) {
        double t = (-b - std::sqrt(discriminant)) / a;
        if (t > t_min && t < t_max) {
            Math::Vector3D hit_point = r.at(t);
            if ((hit_point - position).z >= -1e-6) {  // Only upper hemisphere
                rec.t = t;
                rec.point = hit_point;
                rec.normal = (rec.point - position) / radius;
                rec.setFaceNormal(r, rec.normal);
                rec.material = material;
                return true;
            }
        }
    }
    
    return false;
}

void primitives::Hemisphere::Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material)
{
    this->position = centre;
    this->radius = scale.x;
    this->material = material;
}

extern "C" primitives::IPrimitive *createHemisphere()
{
    return new primitives::Hemisphere();
}
