/*
** EPITECH PROJECT, 2025
** Tetrahedron
** File description:
** Tetrahedron primitive (4 triangular faces)
*/
#include "Tetrahedron.hpp"
#include <cmath>

primitives::Tetrahedron::Tetrahedron() 
    : position(0, 0, 0), radius(1), material(nullptr)
{
}

primitives::Tetrahedron::~Tetrahedron() 
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

bool primitives::Tetrahedron::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    // Regular tetrahedron vertices
    double a = radius * std::sqrt(8.0 / 9.0);
    double b = radius * std::sqrt(2.0 / 9.0);
    double c = radius * std::sqrt(2.0 / 3.0);
    double d = radius / 3.0;
    
    Math::Vector3D v0 = position + Math::Vector3D(0, radius, 0);
    Math::Vector3D v1 = position + Math::Vector3D(-c, -d, -b);
    Math::Vector3D v2 = position + Math::Vector3D(c, -d, -b);
    Math::Vector3D v3 = position + Math::Vector3D(0, -d, a - b);
    
    double closest_t = t_max;
    Math::Vector3D closest_normal;
    bool hit_something = false;
    double t_hit;
    Math::Vector3D n_hit;
    
    // Four triangular faces
    if (hitTriangle(v0, v1, v2, r, t_min, closest_t, t_hit, n_hit)) {
        closest_t = t_hit;
        closest_normal = n_hit;
        hit_something = true;
    }
    if (hitTriangle(v0, v2, v3, r, t_min, closest_t, t_hit, n_hit)) {
        closest_t = t_hit;
        closest_normal = n_hit;
        hit_something = true;
    }
    if (hitTriangle(v0, v3, v1, r, t_min, closest_t, t_hit, n_hit)) {
        closest_t = t_hit;
        closest_normal = n_hit;
        hit_something = true;
    }
    if (hitTriangle(v1, v3, v2, r, t_min, closest_t, t_hit, n_hit)) {
        closest_t = t_hit;
        closest_normal = n_hit;
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

void primitives::Tetrahedron::Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material)
{
    this->position = centre;
    this->radius = scale.x;
    this->material = material;
}

extern "C" primitives::IPrimitive *createTetrahedron()
{
    return new primitives::Tetrahedron();
}
