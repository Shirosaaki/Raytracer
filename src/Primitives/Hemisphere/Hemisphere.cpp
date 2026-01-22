/*
** EPITECH PROJECT, 2025
** Hemisphere
** File description:
** Hemisphere primitive
*/
#include "Hemisphere.hpp"
#include <cmath>

primitives::Hemisphere::Hemisphere() 
    : position(0, 0, 0), scale(1, 1, 1), material(nullptr)
{
}

primitives::Hemisphere::~Hemisphere() 
{
}

bool primitives::Hemisphere::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    // Hemisphere: ellipsoid intersected with y >= 0 plane (in local space)
    Math::Vector3D ray_origin = r.getOrigin() - position;
    Math::Vector3D ray_dir = r.getDirection();
    
    // Apply inverse rotation to ray if needed
    if (rotation.x != 0 || rotation.y != 0 || rotation.z != 0) {
        Math::Vector3D inv_rotation = Math::Vector3D(-rotation.x, -rotation.y, -rotation.z);
        ray_origin = ray_origin.rotate(inv_rotation);
        ray_dir = ray_dir.rotate(inv_rotation);
    }

    // Scale to unit sphere space
    Math::Vector3D oc_scaled = Math::Vector3D(
        ray_origin.x / (scale.x > 0 ? scale.x : 1.0),
        ray_origin.y / (scale.y > 0 ? scale.y : 1.0),
        ray_origin.z / (scale.z > 0 ? scale.z : 1.0)
    );
    Math::Vector3D dir_scaled = Math::Vector3D(
        ray_dir.x / (scale.x > 0 ? scale.x : 1.0),
        ray_dir.y / (scale.y > 0 ? scale.y : 1.0),
        ray_dir.z / (scale.z > 0 ? scale.z : 1.0)
    );

    double a = dir_scaled.dot(dir_scaled);
    double b = 2.0 * oc_scaled.dot(dir_scaled);
    double c = oc_scaled.dot(oc_scaled) - 1.0;
    double discriminant = b * b - 4 * a * c;
    
    // Check intersection with ellipsoid (unit sphere in scaled space)
    double t_sphere = t_max + 1;
    bool sphere_hit = false;
    if (discriminant >= 0) {
        double sqrt_d = std::sqrt(discriminant);
        double t1 = (-b - sqrt_d) / (2 * a);
        double t2 = (-b + sqrt_d) / (2 * a);
        
        auto acceptPoint = [&](double t_candidate) {
            if (t_candidate > t_min && t_candidate < t_max) {
                Math::Vector3D p_local = ray_origin + ray_dir * t_candidate;
                if (p_local.y >= 0) {
                    t_sphere = t_candidate;
                    sphere_hit = true;
                    return true;
                }
            }
            return false;
        };
        if (!acceptPoint(t1)) {
            acceptPoint(t2);
        }
    }
    
    // Check intersection with disk: y = 0, x^2/scale.x^2 + z^2/scale.z^2 <= 1
    double t_disk = t_max + 1;
    bool disk_hit = false;
    if (std::abs(ray_dir.y) > 1e-6) {
        double t = -ray_origin.y / ray_dir.y;
        if (t > t_min && t < t_max) {
            Math::Vector3D p_local = ray_origin + ray_dir * t;
            double x2 = (p_local.x * p_local.x) / ((scale.x > 0 ? scale.x : 1.0) * (scale.x > 0 ? scale.x : 1.0));
            double z2 = (p_local.z * p_local.z) / ((scale.z > 0 ? scale.z : 1.0) * (scale.z > 0 ? scale.z : 1.0));
            if (x2 + z2 <= 1.0 + 1e-6) {
                t_disk = t;
                disk_hit = true;
            }
        }
    }
    
    if (sphere_hit || disk_hit) {
        if (sphere_hit && (!disk_hit || t_sphere < t_disk)) {
            rec.t = t_sphere;
            rec.point = r.at(t_sphere);
            Math::Vector3D p_local = ray_origin + ray_dir * t_sphere;
            Math::Vector3D normal_local = Math::Vector3D(
                p_local.x / (scale.x * scale.x),
                p_local.y / (scale.y * scale.y),
                p_local.z / (scale.z * scale.z)
            ).normalized();
            rec.normal = (rotation.x != 0 || rotation.y != 0 || rotation.z != 0)
                ? normal_local.rotate(rotation)
                : normal_local;
            rec.setFaceNormal(r, rec.normal);
            rec.material = material;
            return true;
        }
        if (disk_hit && (!sphere_hit || t_disk < t_sphere)) {
            rec.t = t_disk;
            rec.point = r.at(t_disk);
            Math::Vector3D normal_local = Math::Vector3D(0, -1, 0);
            rec.normal = (rotation.x != 0 || rotation.y != 0 || rotation.z != 0)
                ? normal_local.rotate(rotation)
                : normal_local;
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
    this->scale = scale;
    this->material = material;
}

extern "C" primitives::IPrimitive *createHemisphere()
{
    return new primitives::Hemisphere();
}
