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
    // Hemisphere: sphere intersected with y >= 0 plane (in local space)
    Math::Vector3D oc = r.getOrigin() - position;
    double a = r.getDirection().dot(r.getDirection());
    double b = 2.0 * oc.dot(r.getDirection());
    double c = oc.dot(oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    
    // Check intersection with sphere
    double t_sphere = t_max + 1;
    bool sphere_hit = false;
    
    if (discriminant >= 0) {
        double t1 = (-b - std::sqrt(discriminant)) / (2*a);
        double t2 = (-b + std::sqrt(discriminant)) / (2*a);
        
        if (t1 > t_min && t1 < t_max) {
             Math::Vector3D p = r.at(t1);
             if ((p.y - position.y) >= 0) {
                 t_sphere = t1;
                 sphere_hit = true;
             }
        }
        if (!sphere_hit && t2 > t_min && t2 < t_max) {
             Math::Vector3D p = r.at(t2);
             if ((p.y - position.y) >= 0) {
                 t_sphere = t2;
                 sphere_hit = true;
             }
        }
    }
    
    // Check intersection with disk: y = 0, x^2 + z^2 <= r^2
    double t_disk = t_max + 1;
    bool disk_hit = false;
    if (std::abs(r.getDirection().y) > 1e-6) {
        double t = (position.y - r.getOrigin().y) / r.getDirection().y;
        if (t > t_min && t < t_max) {
            Math::Vector3D p = r.at(t);
            Math::Vector3D rel = p - position;
            if (rel.x*rel.x + rel.z*rel.z <= radius*radius) {
                t_disk = t;
                disk_hit = true;
            }
        }
    }
    
    if (sphere_hit || disk_hit) {
        if (sphere_hit && (!disk_hit || t_sphere < t_disk)) {
            rec.t = t_sphere;
            rec.point = r.at(t_sphere);
            rec.normal = (rec.point - position) / radius;
            rec.setFaceNormal(r, rec.normal);
            rec.material = material;
            return true;
        } 
        if (disk_hit && (!sphere_hit || t_disk < t_sphere)) {
            rec.t = t_disk;
            rec.point = r.at(t_disk);
            rec.normal = Math::Vector3D(0, -1, 0); // Bottom cap normal
            rec.setFaceNormal(r, rec.normal);
            rec.material = material;
            return true;
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
