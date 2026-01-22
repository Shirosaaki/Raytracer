/*
** EPITECH PROJECT, 2025
** Octahedron
** File description:
** Octahedron primitive (8 triangular faces)
*/
#include "Octahedron.hpp"
#include <cmath>

primitives::Octahedron::Octahedron() 
    : position(0, 0, 0), scaleX(1), scaleY(1), scaleZ(1), material(nullptr)
{
}

primitives::Octahedron::~Octahedron() 
{
}

bool primitives::Octahedron::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    // Apply inverse rotation if needed
    Math::Vector3D ray_origin = r.getOrigin() - position;
    Math::Vector3D ray_direction = r.getDirection();
    if (rotation.x != 0 || rotation.y != 0 || rotation.z != 0) {
        Math::Vector3D inv_rotation = Math::Vector3D(-rotation.x, -rotation.y, -rotation.z);
        ray_origin = ray_origin.rotate(inv_rotation);
        ray_direction = ray_direction.rotate(inv_rotation);
    }
    
    // Regular octahedron with non-uniform scaling
    // sx, sy, sz control dimensions on each axis
    Math::Vector3D top = Math::Vector3D(0, scaleY, 0);
    Math::Vector3D bottom = Math::Vector3D(0, -scaleY, 0);
    Math::Vector3D front = Math::Vector3D(0, 0, scaleZ);
    Math::Vector3D back = Math::Vector3D(0, 0, -scaleZ);
    Math::Vector3D left = Math::Vector3D(-scaleX, 0, 0);
    Math::Vector3D right = Math::Vector3D(scaleX, 0, 0);
    
    double closest_t = t_max;
    Math::Vector3D closest_normal;
    bool hit_something = false;
    double t_hit;
    Math::Vector3D n_hit;
    
    // Lambda for triangle intersection in object space
    auto hitTriangleLocal = [&](const Math::Vector3D& v0, const Math::Vector3D& v1, const Math::Vector3D& v2,
                        double& t_out, Math::Vector3D& normal_out) -> bool {
        Math::Vector3D edge1 = v1 - v0;
        Math::Vector3D edge2 = v2 - v0;
        Math::Vector3D h = ray_direction.cross(edge2);
        double a = edge1.dot(h);
        
        if (std::abs(a) < 1e-8)
            return false;
        
        double f = 1.0 / a;
        Math::Vector3D s = ray_origin - v0;
        double u = f * s.dot(h);
        
        if (u < 0.0 || u > 1.0)
            return false;
        
        Math::Vector3D q = s.cross(edge1);
        double v = f * ray_direction.dot(q);
        
        if (v < 0.0 || u + v > 1.0)
            return false;
        
        double t = f * edge2.dot(q);
        
        if (t > t_min && t < t_max) {
            t_out = t;
            normal_out = edge1.cross(edge2).normalized();
            return true;
        }
        
        return false;
    };
    
    // Top 4 faces
    if (hitTriangleLocal(top, front, right, t_hit, n_hit)) {
        closest_t = t_hit; closest_normal = n_hit; hit_something = true;
    }
    if (hitTriangleLocal(top, right, back, t_hit, n_hit)) {
        closest_t = t_hit; closest_normal = n_hit; hit_something = true;
    }
    if (hitTriangleLocal(top, back, left, t_hit, n_hit)) {
        closest_t = t_hit; closest_normal = n_hit; hit_something = true;
    }
    if (hitTriangleLocal(top, left, front, t_hit, n_hit)) {
        closest_t = t_hit; closest_normal = n_hit; hit_something = true;
    }
    
    // Bottom 4 faces
    if (hitTriangleLocal(bottom, right, front, t_hit, n_hit)) {
        closest_t = t_hit; closest_normal = n_hit; hit_something = true;
    }
    if (hitTriangleLocal(bottom, back, right, t_hit, n_hit)) {
        closest_t = t_hit; closest_normal = n_hit; hit_something = true;
    }
    if (hitTriangleLocal(bottom, left, back, t_hit, n_hit)) {
        closest_t = t_hit; closest_normal = n_hit; hit_something = true;
    }
    if (hitTriangleLocal(bottom, front, left, t_hit, n_hit)) {
        closest_t = t_hit; closest_normal = n_hit; hit_something = true;
    }
    
    if (hit_something) {
        rec.t = closest_t;
        rec.point = ray_origin + (ray_direction * closest_t);
        
        // Transform point and normal back to world space
        if (rotation.x != 0 || rotation.y != 0 || rotation.z != 0) {
            rec.point = rec.point.rotate(rotation);
            closest_normal = closest_normal.rotate(rotation);
        }
        
        rec.point = rec.point + position;
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
    this->scaleX = scale.x;
    this->scaleY = scale.y;
    this->scaleZ = scale.z;
    this->material = material;
}

extern "C" primitives::IPrimitive *createOctahedron()
{
    return new primitives::Octahedron();
}
