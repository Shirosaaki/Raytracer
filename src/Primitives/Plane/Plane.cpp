/*
** EPITECH PROJECT, 2025
** Plane
** File description:
** Plane
*/
#include "Plane.hpp"

primitives::Plane::Plane()
{
    
}

primitives::Plane::~Plane()
{
}

void primitives::Plane::Init(Math::Vector3D centre, Math::Vector3D radius, RayTracer::IMaterials *matherial)
{
    this->position = centre;
    this->matherial = matherial;
    this->axis = radius;
}

bool primitives::Plane::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    double denom = axis.dot(r.direction);
    if (fabs(denom) > 1e-6) {
        Math::Vector3D p0l0 = position - r.origin;
        double t = p0l0.dot(axis) / denom;
        if (t < t_min || t > t_max)
            return false;
        rec.t = t;
        rec.point = r.at(t);
        rec.normal = axis;
        rec.setFaceNormal(r, axis);
        rec.material = matherial;
        return true;
    }
    return false;
}

extern "C" primitives::IPrimitive *createPlane()
{
    return new primitives::Plane();
}
