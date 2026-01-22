/*
** EPITECH PROJECT, 2025
** TriangularPrism
** File description:
** TriangularPrism primitive
*/
#include "TriangularPrism.hpp"
#include <cmath>
#include <vector>
#include <algorithm>

primitives::TriangularPrism::TriangularPrism() 
    : position(0, 0, 0), scale(1, 1, 1), material(nullptr)
{
}

primitives::TriangularPrism::~TriangularPrism() 
{
}

bool primitives::TriangularPrism::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    // Use bounding cylinder: radius from XZ, height from Y
    double radius = (scale.x + scale.z) / 2.0;
    double height = scale.y;
    
    Math::Vector3D r_orig = r.getOrigin() - position;
    Math::Vector3D r_dir = r.getDirection();
    
    // Check Y slab
    double y_min = -height / 2.0;
    double y_max = height / 2.0;
    
    double t_y1 = (y_min - r_orig.y) / r_dir.y;
    double t_y2 = (y_max - r_orig.y) / r_dir.y;
    if (t_y1 > t_y2) std::swap(t_y1, t_y2);
    
    double t_enter_y = std::max(t_min, t_y1);
    double t_exit_y = std::min(t_max, t_y2);
    if (t_enter_y > t_exit_y) return false;
    
    // Check cylinder in XZ
    double a = r_dir.x * r_dir.x + r_dir.z * r_dir.z;
    double b = 2.0 * (r_orig.x * r_dir.x + r_orig.z * r_dir.z);
    double c = r_orig.x * r_orig.x + r_orig.z * r_orig.z - radius * radius;
    
    double disc = b * b - 4 * a * c;
    if (disc < 0) return false;
    
    double sqrt_d = sqrt(disc);
    double t = (-b - sqrt_d) / (2 * a);
    
    if (t < t_min || t > t_max) {
        t = (-b + sqrt_d) / (2 * a);
        if (t < t_min || t > t_max) return false;
    }
    
    // Check if t is within Y bounds
    Math::Vector3D hit_point = r.at(t);
    if (hit_point.y < y_min || hit_point.y > y_max) return false;
    
    rec.t = t;
    rec.point = hit_point;
    rec.normal = Math::Vector3D(hit_point.x - position.x, 0, hit_point.z - position.z);
    rec.normal.normalize();
    rec.setFaceNormal(r, rec.normal);
    rec.material = material;
    return true;
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
