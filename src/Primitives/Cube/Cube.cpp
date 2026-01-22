/*
** EPITECH PROJECT, 2025
** cube
** File description:
** cube
*/
#include "Cube.hpp"

primitives::Cube::Cube()
{
    position = Math::Vector3D(0, 0, 0);
    rotation = Math::Vector3D(0, 0, 0);
    axis = Math::Vector3D(0, 0, 0);
    matherial = nullptr;
}

primitives::Cube::~Cube()
{
    // Destructor implementation (if needed)
}

void primitives::Cube::Init(Math::Vector3D centre, Math::Vector3D radius, RayTracer::IMaterials *matherial)
{
    this->position = centre;
    this->axis = radius;
    this->matherial = matherial;
}

bool primitives::Cube::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    // Translate ray to object space
    Math::Vector3D ray_origin = r.getOrigin() - position;
    
    // Apply inverse rotation to ray
    Math::Vector3D inv_rotation = Math::Vector3D(-rotation.x, -rotation.y, -rotation.z);
    ray_origin = ray_origin.rotate(inv_rotation);
    Math::Vector3D ray_direction = r.getDirection().rotate(inv_rotation);
    
    Math::Vector3D inv_dir = Math::Vector3D(1.0 / ray_direction.x, 1.0 / ray_direction.y, 1.0 / ray_direction.z);
    Math::Vector3D t0 = (Math::Vector3D(0, 0, 0) - ray_origin) * inv_dir;
    Math::Vector3D t1 = (axis - ray_origin) * inv_dir;

    Math::Vector3D t_min_vec = Math::Vector3D(std::min(t0.x, t1.x), std::min(t0.y, t1.y), std::min(t0.z, t1.z));
    Math::Vector3D t_max_vec = Math::Vector3D(std::max(t0.x, t1.x), std::max(t0.y, t1.y), std::max(t0.z, t1.z));

    double t_near = std::max(std::max(t_min_vec.x, t_min_vec.y), std::max(t_min_vec.z, 0.0));
    double t_far = std::min(std::min(t_max_vec.x, t_max_vec.y), std::min(t_max_vec.z, 1.0));

    if (t_near < t_far && t_near < t_max && t_far > t_min) {
        rec.t = t_near;
        rec.point = r.at(rec.t);
        // Compute normal in object space, then rotate back
        Math::Vector3D local_point = rec.point - position;
        local_point = local_point.rotate(inv_rotation);
        Math::Vector3D normal(0, 0, 0);
        if (std::abs(local_point.x - 0) < 0.0001) normal = Math::Vector3D(-1, 0, 0);
        else if (std::abs(local_point.x - axis.x) < 0.0001) normal = Math::Vector3D(1, 0, 0);
        else if (std::abs(local_point.y - 0) < 0.0001) normal = Math::Vector3D(0, -1, 0);
        else if (std::abs(local_point.y - axis.y) < 0.0001) normal = Math::Vector3D(0, 1, 0);
        else if (std::abs(local_point.z - 0) < 0.0001) normal = Math::Vector3D(0, 0, -1);
        else if (std::abs(local_point.z - axis.z) < 0.0001) normal = Math::Vector3D(0, 0, 1);
        
        // Rotate normal back to world space
        normal = normal.rotate(rotation);
        rec.normal = normal.normalized();
        rec.setFaceNormal(r, rec.normal);
        rec.material = matherial;
        return true;
    }
    return false;
}

extern "C" primitives::IPrimitive *createCube()
{
    return new primitives::Cube();
}
