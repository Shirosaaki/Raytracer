/*
** EPITECH PROJECT, 2025
** Pyramid
** File description:
** Pyramid primitive (square base)
*/
#include "Pyramid.hpp"
#include <cmath>
#include <algorithm>

primitives::Pyramid::Pyramid() 
    : position(0, 0, 0), scale(1, 1, 1), material(nullptr)
{
}

primitives::Pyramid::~Pyramid() 
{
}

static bool hitTriangle(const Math::Vector3D& v0, const Math::Vector3D& v1, const Math::Vector3D& v2,
                        const RayTracer::Ray& r, double t_min, double t_max, 
                        double& t_out, Math::Vector3D& normal_out)
{
    Math::Vector3D edge1 = v1 - v0;
    Math::Vector3D edge2 = v2 - v0;
    Math::Vector3D h = r.getDirection().cross(edge2);
    double a = edge1.dot(h);
    
    if (std::abs(a) < 1e-8)
        return false;
    
    double f = 1.0 / a;
    Math::Vector3D s = r.getOrigin() - v0;
    double u = f * s.dot(h);
    
    if (u < 0.0 || u > 1.0)
        return false;
    
    Math::Vector3D q = s.cross(edge1);
    double v = f * r.getDirection().dot(q);
    
    if (v < 0.0 || u + v > 1.0)
        return false;
    
    double t = f * edge2.dot(q);
    
    if (t > t_min && t < t_max) {
        t_out = t;
        normal_out = edge1.cross(edge2).normalized();
        return true;
    }
    
    return false;
}

bool primitives::Pyramid::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    double half_base = scale.x / 2.0;
    double height = scale.z;
    
    // Apex at top
    Math::Vector3D apex = position + Math::Vector3D(0, height, 0);
    
    // Base vertices (square)
    Math::Vector3D b0 = position + Math::Vector3D(-half_base, 0, -half_base);
    Math::Vector3D b1 = position + Math::Vector3D(half_base, 0, -half_base);
    Math::Vector3D b2 = position + Math::Vector3D(half_base, 0, half_base);
    Math::Vector3D b3 = position + Math::Vector3D(-half_base, 0, half_base);
    
    double closest_t = t_max;
    Math::Vector3D closest_normal;
    bool hit_something = false;
    double t_hit;
    Math::Vector3D n_hit;
    
    // Four triangular faces
    if (hitTriangle(apex, b0, b1, r, t_min, closest_t, t_hit, n_hit)) {
        closest_t = t_hit;
        closest_normal = n_hit;
        hit_something = true;
    }
    if (hitTriangle(apex, b1, b2, r, t_min, closest_t, t_hit, n_hit)) {
        closest_t = t_hit;
        closest_normal = n_hit;
        hit_something = true;
    }
    if (hitTriangle(apex, b2, b3, r, t_min, closest_t, t_hit, n_hit)) {
        closest_t = t_hit;
        closest_normal = n_hit;
        hit_something = true;
    }
    if (hitTriangle(apex, b3, b0, r, t_min, closest_t, t_hit, n_hit)) {
        closest_t = t_hit;
        closest_normal = n_hit;
        hit_something = true;
    }
    
    // Base (two triangles)
    if (hitTriangle(b0, b2, b1, r, t_min, closest_t, t_hit, n_hit)) {
        closest_t = t_hit;
        closest_normal = Math::Vector3D(0, -1, 0);
        hit_something = true;
    }
    if (hitTriangle(b0, b3, b2, r, t_min, closest_t, t_hit, n_hit)) {
        closest_t = t_hit;
        closest_normal = Math::Vector3D(0, -1, 0);
        hit_something = true;
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

void primitives::Pyramid::Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material)
{
    this->position = centre;
    this->scale = scale;
    this->material = material;
}

extern "C" primitives::IPrimitive *createPyramid()
{
    return new primitives::Pyramid();
}
