/*
** EPITECH PROJECT, 2025
** TriangularPrism
** File description:
** TriangularPrism primitive
*/
#include "TriangularPrism.hpp"
#include <cmath>

primitives::TriangularPrism::TriangularPrism() 
    : position(0, 0, 0), scale(1, 1, 1), material(nullptr)
{
}

primitives::TriangularPrism::~TriangularPrism() 
{
}

bool primitives::TriangularPrism::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    // Simplified triangular prism hit detection using bounding box
    Math::Vector3D oc = r.getOrigin() - position;
    Math::Vector3D dir = r.getDirection();
    
    // Check base intersection (triangle at z)
    double denom = dir.z;
    if (std::abs(denom) > 1e-6) {
        double t = -oc.z / denom;
        if (t > t_min && t < t_max) {
            Math::Vector3D hit_point = r.at(t);
            Math::Vector3D rel = hit_point - position;
            
            // Triangle bounds check (simplified)
            if (std::abs(rel.x) < scale.x && std::abs(rel.y) < scale.y) {
                rec.t = t;
                rec.point = hit_point;
                rec.normal = Math::Vector3D(0, 0, 1);
                rec.setFaceNormal(r, rec.normal);
                rec.material = material;
                return true;
            }
        }
    }
    
    return false;
}

void primitives::TriangularPrism::Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material)
{
    this->position = centre;
    this->scale = scale;
    this->material = material;
}

extern "C" primitives::IPrimitive *createTriangularPrism()
{
    return new primitives::TriangularPrism();
}
