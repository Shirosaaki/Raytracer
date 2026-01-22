/*
** EPITECH PROJECT, 2025
** Cone
** File description:
** Cone primitive
*/
#include "Cone.hpp"
#include <cmath>

primitives::Cone::Cone() 
    : position(0, 0, 0), scale(1, 1, 1), material(nullptr)
{
}

primitives::Cone::~Cone() 
{
}

bool primitives::Cone::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    // Transform ray to object space
    Math::Vector3D ray_origin = r.getOrigin() - position;
    Math::Vector3D ray_direction = r.getDirection();
    
    // Apply inverse rotation if needed
    if (rotation.x != 0 || rotation.y != 0 || rotation.z != 0) {
        Math::Vector3D inv_rotation = Math::Vector3D(-rotation.x, -rotation.y, -rotation.z);
        ray_origin = ray_origin.rotate(inv_rotation);
        ray_direction = ray_direction.rotate(inv_rotation);
    }
    
    // Finite cone along Y axis with apex at origin and base at -height
    double height = scale.z;
    double radius = scale.x;
    double tan_angle = radius / height;
    double tan2 = tan_angle * tan_angle;
    
    Math::Vector3D oc = ray_origin;
    Math::Vector3D dir = ray_direction;
    
    // Cone equation: x² + z² = (tan(angle) * (apex_y - y))²
    double a = dir.x * dir.x + dir.z * dir.z - tan2 * dir.y * dir.y;
    double b = 2.0 * (oc.x * dir.x + oc.z * dir.z - tan2 * oc.y * dir.y);
    double c = oc.x * oc.x + oc.z * oc.z - tan2 * oc.y * oc.y;
    
    double discriminant = b * b - 4.0 * a * c;
    
    if (discriminant < 0)
        return false;
    
    double sqrt_d = std::sqrt(discriminant);
    double t = (-b - sqrt_d) / (2.0 * a);
    
    if (t < t_min || t > t_max) {
        t = (-b + sqrt_d) / (2.0 * a);
        if (t < t_min || t > t_max)
            return false;
    }
    
    double hit_y = oc.y + t * dir.y;
    
    // Check if hit is within cone height (y between -height and 0)
    if (hit_y > 0 || hit_y < -height)
        return false;
    
    rec.t = t;
    rec.point = r.at(t);
    
    // Calculate normal in object space
    double hit_x = oc.x + t * dir.x;
    double hit_z = oc.z + t * dir.z;
    double r_at_y = -hit_y * tan_angle;
    Math::Vector3D outward = Math::Vector3D(hit_x, 0, hit_z);
    if (outward.length() > 1e-6)
        outward = outward.normalized() * height;
    Math::Vector3D normal_local = Math::Vector3D(outward.x, r_at_y, outward.z).normalized();
    
    // Transform normal back to world space
    if (rotation.x != 0 || rotation.y != 0 || rotation.z != 0) {
        normal_local = normal_local.rotate(rotation);
    }
    
    rec.normal = normal_local.normalized();
    rec.setFaceNormal(r, rec.normal);
    rec.material = material;
    
    return true;
}

void primitives::Cone::Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material)
{
    this->position = centre;
    this->scale = scale;
    this->material = material;
}

extern "C" primitives::IPrimitive *createCone()
{
    return new primitives::Cone();
}
