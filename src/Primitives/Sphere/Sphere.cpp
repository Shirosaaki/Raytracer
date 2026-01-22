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
    scaleX = 0;
    scaleY = 0;
    scaleZ = 0;
    rotation = Math::Vector3D(0, 0, 0);
    matherial = nullptr;
}

primitives::Sphere::~Sphere() 
{
    // Destructor implementation (if needed)
}

bool primitives::Sphere::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    // For true non-uniform sphere, treat as ellipsoid with scaleX, scaleY, scaleZ
    // Transform ray to ellipsoid space
    Math::Vector3D oc = r.getOrigin() - position;
    Math::Vector3D dir_scaled = Math::Vector3D(
        r.getDirection().x / (scaleX > 0 ? scaleX : 1.0),
        r.getDirection().y / (scaleY > 0 ? scaleY : 1.0),
        r.getDirection().z / (scaleZ > 0 ? scaleZ : 1.0)
    );
    Math::Vector3D oc_scaled = Math::Vector3D(
        oc.x / (scaleX > 0 ? scaleX : 1.0),
        oc.y / (scaleY > 0 ? scaleY : 1.0),
        oc.z / (scaleZ > 0 ? scaleZ : 1.0)
    );
    
    double a = dir_scaled.dot(dir_scaled);
    double b = oc_scaled.dot(dir_scaled);
    double c = oc_scaled.dot(oc_scaled) - 1.0;
    double discriminant = b * b - a * c;
    
    if (discriminant > 0) {
        double temp = (-b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.point = r.at(rec.t);
            Math::Vector3D normal_scaled = Math::Vector3D(
                (rec.point.x - position.x) / (scaleX * scaleX),
                (rec.point.y - position.y) / (scaleY * scaleY),
                (rec.point.z - position.z) / (scaleZ * scaleZ)
            );
            rec.normal = normal_scaled.normalized();
            rec.setFaceNormal(r, rec.normal);
            rec.material = matherial;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.point = r.at(rec.t);
            Math::Vector3D normal_scaled = Math::Vector3D(
                (rec.point.x - position.x) / (scaleX * scaleX),
                (rec.point.y - position.y) / (scaleY * scaleY),
                (rec.point.z - position.z) / (scaleZ * scaleZ)
            );
            rec.normal = normal_scaled.normalized();
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
    this->scaleX = radius.x;
    this->scaleY = radius.y;
    this->scaleZ = radius.z;
    this->matherial = matherial;
}

extern "C" primitives::IPrimitive *createSphere()
{
    return new primitives::Sphere();
}
