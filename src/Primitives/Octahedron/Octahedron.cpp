/*
** EPITECH PROJECT, 2025
** Octahedron
** File description:
** Octahedron primitive (8 triangular faces)
*/
#include "Octahedron.hpp"
#include <cmath>

primitives::Octahedron::Octahedron() 
    : position(0, 0, 0), radius(1), material(nullptr)
{
}

primitives::Octahedron::~Octahedron() 
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

bool primitives::Octahedron::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    // Regular octahedron: 6 vertices, 8 triangular faces
    Math::Vector3D top = position + Math::Vector3D(0, radius, 0);
    Math::Vector3D bottom = position + Math::Vector3D(0, -radius, 0);
    Math::Vector3D front = position + Math::Vector3D(0, 0, radius);
    Math::Vector3D back = position + Math::Vector3D(0, 0, -radius);
    Math::Vector3D left = position + Math::Vector3D(-radius, 0, 0);
    Math::Vector3D right = position + Math::Vector3D(radius, 0, 0);
    
    double closest_t = t_max;
    Math::Vector3D closest_normal;
    bool hit_something = false;
    double t_hit;
    Math::Vector3D n_hit;
    
    // Top 4 faces
    if (hitTriangle(top, front, right, r, t_min, closest_t, t_hit, n_hit)) {
        closest_t = t_hit; closest_normal = n_hit; hit_something = true;
    }
    if (hitTriangle(top, right, back, r, t_min, closest_t, t_hit, n_hit)) {
        closest_t = t_hit; closest_normal = n_hit; hit_something = true;
    }
    if (hitTriangle(top, back, left, r, t_min, closest_t, t_hit, n_hit)) {
        closest_t = t_hit; closest_normal = n_hit; hit_something = true;
    }
    if (hitTriangle(top, left, front, r, t_min, closest_t, t_hit, n_hit)) {
        closest_t = t_hit; closest_normal = n_hit; hit_something = true;
    }
    
    // Bottom 4 faces
    if (hitTriangle(bottom, right, front, r, t_min, closest_t, t_hit, n_hit)) {
        closest_t = t_hit; closest_normal = n_hit; hit_something = true;
    }
    if (hitTriangle(bottom, back, right, r, t_min, closest_t, t_hit, n_hit)) {
        closest_t = t_hit; closest_normal = n_hit; hit_something = true;
    }
    if (hitTriangle(bottom, left, back, r, t_min, closest_t, t_hit, n_hit)) {
        closest_t = t_hit; closest_normal = n_hit; hit_something = true;
    }
    if (hitTriangle(bottom, front, left, r, t_min, closest_t, t_hit, n_hit)) {
        closest_t = t_hit; closest_normal = n_hit; hit_something = true;
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

void primitives::Octahedron::Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material)
{
    this->position = centre;
    this->radius = scale.x;
    this->material = material;
}

extern "C" primitives::IPrimitive *createOctahedron()
{
    return new primitives::Octahedron();
}
