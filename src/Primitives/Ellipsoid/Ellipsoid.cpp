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
    // Proper ellipsoid intersection using non-uniform scaling
    Math::Vector3D oc = r.getOrigin() - position;
    Math::Vector3D ray_dir = r.getDirection();
    
    // Apply inverse rotation to ray if needed
    if (rotation.x != 0 || rotation.y != 0 || rotation.z != 0) {
        Math::Vector3D inv_rotation = Math::Vector3D(-rotation.x, -rotation.y, -rotation.z);
        oc = oc.rotate(inv_rotation);
        ray_dir = ray_dir.rotate(inv_rotation);
    }
    
    // Transform to unit sphere space
    Math::Vector3D oc_scaled = Math::Vector3D(
        oc.x / (scale.x > 0 ? scale.x : 1.0),
        oc.y / (scale.y > 0 ? scale.y : 1.0),
        oc.z / (scale.z > 0 ? scale.z : 1.0)
    );
    Math::Vector3D dir_scaled = Math::Vector3D(
        ray_dir.x / (scale.x > 0 ? scale.x : 1.0),
        ray_dir.y / (scale.y > 0 ? scale.y : 1.0),
        ray_dir.z / (scale.z > 0 ? scale.z : 1.0)
    );
    
    double a = dir_scaled.dot(dir_scaled);
    double b = oc_scaled.dot(dir_scaled);
    double c = oc_scaled.dot(oc_scaled) - 1.0;
    
    double discriminant = b * b - a * c;
    if (discriminant < 0) return false;
    
    double sqrt_d = sqrt(discriminant);
    double t = (-b - sqrt_d) / a;
    
    if (t < t_min || t > t_max) {
        t = (-b + sqrt_d) / a;
        if (t < t_min || t > t_max)
            return false;
    }
    
    rec.t = t;
    rec.point = r.at(t);
    
    // Calculate normal in scaled space, then transform back
    Math::Vector3D point_scaled = Math::Vector3D(
        (rec.point.x - position.x) / (scale.x * scale.x),
        (rec.point.y - position.y) / (scale.y * scale.y),
        (rec.point.z - position.z) / (scale.z * scale.z)
    );
    rec.normal = point_scaled.normalized();
    
    // Transform normal back to world space
    if (rotation.x != 0 || rotation.y != 0 || rotation.z != 0) {
        rec.normal = rec.normal.rotate(rotation);
    }
    
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
