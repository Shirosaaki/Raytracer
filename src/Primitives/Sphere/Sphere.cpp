/*
** EPITECH PROJECT, 2025
** Sphere
** File description:
** Sphere
*/
#include "Sphere.hpp"

primitives::Sphere::Sphere() 
{
    position = Math::Vector3D(0, 0, 0);
    radius = Math::Vector3D(0, 0, 0);
    rotation = Math::Vector3D(0, 0, 0);
    matherial = nullptr;
    dRadius = 0;
}

primitives::Sphere::~Sphere() 
{
    // Destructor implementation (if needed)
}

bool primitives::Sphere::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    Math::Vector3D oc = r.getOrigin() - position;
    
    double a = r.getDirection().dot(r.getDirection());
    double b = oc.dot(r.getDirection());
    double c = oc.dot(oc) - dRadius*dRadius;
    double discriminant = b * b - a * c;
    if (discriminant > 0) {
        double temp = (-b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.point = r.at(rec.t);
            rec.normal = (rec.point - position) / dRadius;
            rec.setFaceNormal(r, rec.normal);
            rec.material = matherial;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.point = r.at(rec.t);
            rec.normal = (rec.point - position) / dRadius;
            rec.setFaceNormal(r, rec.normal);
            rec.material = matherial;
            return true;
        }
    }
    return false;
}

void primitives::Sphere::Init(Math::Vector3D centre, Math::Vector3D radius, RayTracer::IMaterials *matherial)
{
    this->position = centre;
    this->radius = radius;
    this->matherial = matherial;
    dRadius = radius.x;
}

extern "C" primitives::IPrimitive *createSphere()
{
    return new primitives::Sphere();
}
