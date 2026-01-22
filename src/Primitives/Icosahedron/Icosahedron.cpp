/*
** EPITECH PROJECT, 2025
** Icosahedron
** File description:
** Icosahedron primitive
*/
#include "Icosahedron.hpp"
#include <cmath>
#include <vector>
#include <algorithm>

primitives::Icosahedron::Icosahedron() 
    : position(0, 0, 0), scale(1, 1, 1), material(nullptr)
{
}

primitives::Icosahedron::~Icosahedron() 
{
}

bool primitives::Icosahedron::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    Math::Vector3D r_orig = r.getOrigin() - position;
    Math::Vector3D r_d = r.getDirection();
    
    // Apply inverse rotation to ray if needed
    if (rotation.x != 0 || rotation.y != 0 || rotation.z != 0) {
        Math::Vector3D inv_rotation = Math::Vector3D(-rotation.x, -rotation.y, -rotation.z);
        r_orig = r_orig.rotate(inv_rotation);
        r_d = r_d.rotate(inv_rotation);
    }
    
    // Non-uniform scaling factors
    double sx = scale.x;
    double sy = scale.y;
    double sz = scale.z;
    
    // Golden ratio
    double phi = (1.0 + std::sqrt(5.0)) / 2.0;
    
    // Vertices of unit icosahedron
    std::vector<Math::Vector3D> verts = {
        {-1,  phi, 0}, { 1,  phi, 0}, {-1, -phi, 0}, { 1, -phi, 0},
        { 0, -1,  phi}, { 0,  1,  phi}, { 0, -1, -phi}, { 0,  1, -phi},
        { phi, 0, -1}, { phi, 0,  1}, {-phi, 0, -1}, {-phi, 0,  1}
    };
    
    // Indices for 20 faces
    int faces[20][3] = {
        {0, 11, 5}, {0, 5, 1}, {0, 1, 7}, {0, 7, 10}, {0, 10, 11},
        {1, 5, 9}, {5, 11, 4}, {11, 10, 2}, {10, 7, 6}, {7, 1, 8},
        {3, 9, 4}, {3, 4, 2}, {3, 2, 6}, {3, 6, 8}, {3, 8, 9},
        {4, 9, 5}, {2, 4, 11}, {6, 2, 10}, {8, 6, 7}, {9, 8, 1}
    };
    
    double t0 = t_min, t1 = t_max;
    Math::Vector3D n0, n1;
    bool hit = true;
    
    for (int i = 0; i < 20; ++i) {
        Math::Vector3D v1 = verts[faces[i][0]];
        Math::Vector3D v2 = verts[faces[i][1]];
        Math::Vector3D v3 = verts[faces[i][2]];
        
        // Scale vertices with non-uniform scaling on each axis
        v1 = Math::Vector3D(v1.x * sx, v1.y * sy, v1.z * sz);
        v2 = Math::Vector3D(v2.x * sx, v2.y * sy, v2.z * sz);
        v3 = Math::Vector3D(v3.x * sx, v3.y * sy, v3.z * sz);
        
        Math::Vector3D normal = (v2 - v1).cross(v3 - v1);
        normal.normalize();
        
        // Plane eq: N.P + d = 0.
        // d = -N.v1
        double d = -normal.dot(v1);
        
        // Intersection with half space
        double numer = -(normal.dot(r_orig) + d);
        double denom = normal.dot(r_d);
        
        if (std::abs(denom) < 1e-9) {
             if (numer < 0) { hit = false; break; }
        } else {
             double t = numer / denom;
             if (denom > 0) {
                 if (t < t1) { t1 = t; n1 = normal; }
             } else {
                 if (t > t0) { t0 = t; n0 = normal; }
             }
             if (t0 > t1) { hit = false; break; }
        }
    }
    
    if (hit && t0 < t_max && t0 > t_min) {
        rec.t = t0;
        rec.point = r.at(t0);
        
        // Transform normal back to world space
        if (rotation.x != 0 || rotation.y != 0 || rotation.z != 0) {
            n0 = n0.rotate(rotation);
        }
        
        rec.normal = n0;
        rec.setFaceNormal(r, rec.normal);
        rec.material = material;
        return true;
    }

    return false;
}

void primitives::Icosahedron::Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material)
{
    this->position = centre;
    this->scale = scale;
    this->material = material;
}

extern "C" primitives::IPrimitive *createIcosahedron()
{
    return new primitives::Icosahedron();
}
