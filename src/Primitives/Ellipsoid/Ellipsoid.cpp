/*
** EPITECH PROJECT, 2025
** Ellipsoid
** File description:
** Ellipsoid primitive
*/
#include "Ellipsoid.hpp"
#include <cmath>

primitives::Ellipsoid::Ellipsoid() 
    : position(0, 0, 0), scale(1, 1, 1), material(nullptr)
{
}

primitives::Ellipsoid::~Ellipsoid() 
{
}

bool primitives::Ellipsoid::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    // Ellipsoid hit detection
    Math::Vector3D oc = r.getOrigin() - position;
    Math::Vector3D dir = r.getDirection();
    
    double a = (dir.x * dir.x) / (scale.x * scale.x) + (dir.y * dir.y) / (scale.y * scale.y) + (dir.z * dir.z) / (scale.z * scale.z);
    double b = 2 * ((oc.x * dir.x) / (scale.x * scale.x) + (oc.y * dir.y) / (scale.y * scale.y) + (oc.z * dir.z) / (scale.z * scale.z));
    double c = (oc.x * oc.x) / (scale.x * scale.x) + (oc.y * oc.y) / (scale.y * scale.y) + (oc.z * oc.z) / (scale.z * scale.z) - 1;
    
    double discriminant = b * b - 4 * a * c;
    if (discriminant >= 0 && std::abs(a) > 1e-6) {
        double t = (-b - std::sqrt(discriminant)) / (2 * a);
        if (t > t_min && t < t_max) {
            rec.t = t;
            rec.point = r.at(t);
            rec.normal = Math::Vector3D(rec.point.x / (scale.x * scale.x), 
                                        rec.point.y / (scale.y * scale.y), 
                                        rec.point.z / (scale.z * scale.z)).normalized();
            rec.setFaceNormal(r, rec.normal);
            rec.material = material;
            return true;
        }
    }
    
    return false;
}

void primitives::Ellipsoid::Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material)
{
    this->position = centre;
    this->scale = scale;
    this->material = material;
}

extern "C" primitives::IPrimitive *createEllipsoid()
{
    return new primitives::Ellipsoid();
}
