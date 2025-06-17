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
    this->rotation = radius;
    this->matherial = matherial;
    this->axis = radius;
}

bool primitives::Cube::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    Math::Vector3D inv_dir = Math::Vector3D(1.0 / r.getDirection().x, 1.0 / r.getDirection().y, 1.0 / r.getDirection().z);
    Math::Vector3D t0 = (position - r.getOrigin()) * inv_dir;
    Math::Vector3D t1 = (position + axis - r.getOrigin()) * inv_dir;

    Math::Vector3D t_min_vec = Math::Vector3D(std::min(t0.x, t1.x), std::min(t0.y, t1.y), std::min(t0.z, t1.z));
    Math::Vector3D t_max_vec = Math::Vector3D(std::max(t0.x, t1.x), std::max(t0.y, t1.y), std::max(t0.z, t1.z));

    double t_near = std::max(std::max(t_min_vec.x, t_min_vec.y), std::max(t_min_vec.z, 0.0));
    double t_far = std::min(std::min(t_max_vec.x, t_max_vec.y), std::min(t_max_vec.z, 1.0));

    if (t_near < t_far && t_near < t_max && t_far > t_min) {
        rec.t = t_near;
        rec.point = r.at(rec.t);
        rec.normal = (rec.point - position).normalized();
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
