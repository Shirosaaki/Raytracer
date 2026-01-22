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
    // Finite cylinder along Y axis
    double radius = scale.x;
    double half_height = scale.z / 2.0;
    
    Math::Vector3D oc = r.getOrigin() - position;
    Math::Vector3D dir = r.getDirection();
    
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
            Math::Vector3D p = r.at(t1);
            double y_local = p.y - position.y;
            if (y_local >= -half_height && y_local <= half_height) {
                closest_t = t1;
                closest_normal = Math::Vector3D(p.x - position.x, 0, p.z - position.z).normalized();
                hit_something = true;
            }
        }
        
        double t2 = (-b + sqrt_d) / (2.0 * a);
        if (t2 > t_min && t2 < closest_t) {
            Math::Vector3D p = r.at(t2);
            double y_local = p.y - position.y;
            if (y_local >= -half_height && y_local <= half_height) {
                closest_t = t2;
                closest_normal = Math::Vector3D(p.x - position.x, 0, p.z - position.z).normalized();
                hit_something = true;
            }
        }
    }
    
    // Check top cap
    if (std::abs(dir.y) > 1e-6) {
        double t_top = (position.y + half_height - r.getOrigin().y) / dir.y;
        if (t_top > t_min && t_top < closest_t) {
            Math::Vector3D p = r.at(t_top);
            double dist = (p.x - position.x) * (p.x - position.x) + (p.z - position.z) * (p.z - position.z);
            if (dist <= radius * radius) {
                closest_t = t_top;
                closest_normal = Math::Vector3D(0, 1, 0);
                hit_something = true;
            }
        }
        
        // Check bottom cap
        double t_bot = (position.y - half_height - r.getOrigin().y) / dir.y;
        if (t_bot > t_min && t_bot < closest_t) {
            Math::Vector3D p = r.at(t_bot);
            double dist = (p.x - position.x) * (p.x - position.x) + (p.z - position.z) * (p.z - position.z);
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
        rec.normal = closest_normal;
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
