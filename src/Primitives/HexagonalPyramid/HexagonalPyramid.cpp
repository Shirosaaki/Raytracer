/*
** EPITECH PROJECT, 2025
** HexagonalPyramid
** File description:
** HexagonalPyramid primitive
*/
#include "HexagonalPyramid.hpp"
#include <cmath>

primitives::HexagonalPyramid::HexagonalPyramid() 
    : position(0, 0, 0), scale(1, 1, 1), material(nullptr)
{
}

primitives::HexagonalPyramid::~HexagonalPyramid() 
{
}

bool primitives::HexagonalPyramid::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    // Simplified hexagonal pyramid using bounding box
    Math::Vector3D oc = r.getOrigin() - position;
    
    // Check base intersection (hexagon at z - height/2)
    double denom = r.getDirection().z;
    if (std::abs(denom) > 1e-6) {
        double t = (-oc.z - scale.z / 2) / denom;
        if (t > t_min && t < t_max) {
            Math::Vector3D hit_point = r.at(t);
            Math::Vector3D rel_point = hit_point - position;
            
            // Hexagon bounds check (simplified as circle)
            double dist = std::sqrt(rel_point.x * rel_point.x + rel_point.y * rel_point.y);
            if (dist < scale.x) {
                rec.t = t;
                rec.point = hit_point;
                rec.normal = Math::Vector3D(0, 0, -1);
                rec.setFaceNormal(r, rec.normal);
                rec.material = material;
                return true;
            }
        }
    }
    
    return false;
}

void primitives::HexagonalPyramid::Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material)
{
    this->position = centre;
    this->scale = scale;
    this->material = material;
}

extern "C" primitives::IPrimitive *createHexagonalPyramid()
{
    return new primitives::HexagonalPyramid();
}
