/*
** EPITECH PROJECT, 2025
** Cylinder
** File description:
** Cylinder primitive
*/
#include "Cylinder.hpp"
#include <cmath>

primitives::Cylinder::Cylinder() 
    : position(0, 0, 0), scale(1, 1, 1), material(nullptr)
{
}

primitives::Cylinder::~Cylinder() 
{
}

bool primitives::Cylinder::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
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
    
    // Finite cylinder along Y axis
    double radius = scale.x;
    double half_height = scale.z / 2.0;
    
    Math::Vector3D oc = ray_origin;
    Math::Vector3D dir = ray_direction;
    
    // Cylinder side: x² + z² = radius²
    double a = dir.x * dir.x + dir.z * dir.z;
    double b = 2.0 * (oc.x * dir.x + oc.z * dir.z);
    double c = oc.x * oc.x + oc.z * oc.z - radius * radius;
    
    double closest_t = t_max;
    Math::Vector3D closest_normal;
    bool hit_something = false;
    
    // Check cylinder sides
    double discriminant = b * b - 4.0 * a * c;
    if (discriminant >= 0 && std::abs(a) > 1e-6) {
        double sqrt_d = std::sqrt(discriminant);
        
        double t1 = (-b - sqrt_d) / (2.0 * a);
        if (t1 > t_min && t1 < closest_t) {
            double py = oc.y + t1 * dir.y;
            if (py >= -half_height && py <= half_height) {
                double px = oc.x + t1 * dir.x;
                double pz = oc.z + t1 * dir.z;
                closest_t = t1;
                closest_normal = Math::Vector3D(px, 0, pz).normalized();
                hit_something = true;
            }
        }
        
        double t2 = (-b + sqrt_d) / (2.0 * a);
        if (t2 > t_min && t2 < closest_t) {
            double py = oc.y + t2 * dir.y;
            if (py >= -half_height && py <= half_height) {
                double px = oc.x + t2 * dir.x;
                double pz = oc.z + t2 * dir.z;
                closest_t = t2;
                closest_normal = Math::Vector3D(px, 0, pz).normalized();
                hit_something = true;
            }
        }
    }
    
    // Check top cap
    if (std::abs(dir.y) > 1e-6) {
        double t_top = (half_height - oc.y) / dir.y;
        if (t_top > t_min && t_top < closest_t) {
            double px = oc.x + t_top * dir.x;
            double pz = oc.z + t_top * dir.z;
            double dist = px * px + pz * pz;
            if (dist <= radius * radius) {
                closest_t = t_top;
                closest_normal = Math::Vector3D(0, 1, 0);
                hit_something = true;
            }
        }
        
        // Check bottom cap
        double t_bot = (-half_height - oc.y) / dir.y;
        if (t_bot > t_min && t_bot < closest_t) {
            double px = oc.x + t_bot * dir.x;
            double pz = oc.z + t_bot * dir.z;
            double dist = px * px + pz * pz;
            if (dist <= radius * radius) {
                closest_t = t_bot;
                closest_normal = Math::Vector3D(0, -1, 0);
                hit_something = true;
            }
        }
    }
    
    if (hit_something) {
        rec.t = closest_t;
        rec.point = r.at(closest_t);
        
        // Transform normal back to world space
        if (rotation.x != 0 || rotation.y != 0 || rotation.z != 0) {
            closest_normal = closest_normal.rotate(rotation);
        }
        
        rec.normal = closest_normal.normalized();
        rec.setFaceNormal(r, rec.normal);
        rec.material = material;
        return true;
    }
    
    return false;
}

void primitives::Cylinder::Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material)
{
    this->position = centre;
    this->scale = scale;
    this->material = material;
}

extern "C" primitives::IPrimitive *createCylinder()
{
    return new primitives::Cylinder();
}
