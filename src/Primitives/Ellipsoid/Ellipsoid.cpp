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
    // Use bounding sphere with average scale
    double radius = (scale.x + scale.y + scale.z) / 3.0;
    
    Math::Vector3D oc = r.getOrigin() - position;
    double a = r.getDirection().dot(r.getDirection());
    double b = 2.0 * oc.dot(r.getDirection());
    double c = oc.dot(oc) - radius * radius;
    
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return false;
    
    double sqrt_d = sqrt(discriminant);
    double t = (-b - sqrt_d) / (2 * a);
    
    if (t < t_min || t > t_max) {
        t = (-b + sqrt_d) / (2 * a);
        if (t < t_min || t > t_max)
            return false;
    }
    
    rec.t = t;
    rec.point = r.at(t);
    rec.normal = (rec.point - position) / radius;
    rec.setFaceNormal(r, rec.normal);
    rec.material = material;
    return true;
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
