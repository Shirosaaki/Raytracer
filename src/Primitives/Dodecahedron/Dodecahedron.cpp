/*
** EPITECH PROJECT, 2025
** Dodecahedron
** File description:
** Dodecahedron primitive
*/
#include "Dodecahedron.hpp"
#include <cmath>
#include <vector>
#include <algorithm>

primitives::Dodecahedron::Dodecahedron() 
    : position(0, 0, 0), radius(1), material(nullptr)
{
}

primitives::Dodecahedron::~Dodecahedron() 
{
}

bool primitives::Dodecahedron::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    Math::Vector3D r_orig = r.getOrigin() - position;
    Math::Vector3D r_d = r.getDirection();
    double s = radius; // Scale factor
    
    double phi = (1.0 + std::sqrt(5.0)) / 2.0; // 1.618
    double inv_phi = 1.0 / phi; // 0.618
    
    // Normals are vertices of Icosahedron (12)
    std::vector<Math::Vector3D> normals = {
        {0, 1, phi}, {0, 1, -phi}, {0, -1, phi}, {0, -1, -phi},
        {1, phi, 0}, {1, -phi, 0}, {-1, phi, 0}, {-1, -phi, 0},
        {phi, 0, 1}, {phi, 0, -1}, {-phi, 0, 1}, {-phi, 0, -1}
    };
    
    // One vertex of Dodecahedron is (1, 1, 1).
    // Let's compute d for the first normal (0, 1, phi).
    // We need max(dot(N, V)) over all vertices V.
    // Or simpler: The face center in direction (0, 1, phi) is ...
    // Actually, (0, phi, 1/phi) is a Vertex?
    // Dodecahedron vertices: (0, +/-phi, +/-1/phi).
    // Let's take vertex V = (0, phi, 1/phi).
    // Normal N = (0, 1, phi). Normalize N -> (0, 1, phi) / sqrt(1+phi^2).
    // dot((0, phi, 1/phi), (0, 1, phi)) = phi + 1.
    // Length of N is sqrt(1 + phi*phi).
    // phi^2 = phi + 1. So length is sqrt(phi+2).
    // Normalize N.
    
    // Just find d dynamically once? Or hardcode.
    // Let's use max projection loop for robustness.
    
    std::vector<Math::Vector3D> vertices;
    // (+-1, +-1, +-1)
    for (int i=0; i<8; i++) vertices.push_back({(i&1 ? -1.0:1.0), (i&2 ? -1.0:1.0), (i&4 ? -1.0:1.0)});
    // (0, +-phi, +-1/phi)
    for (int i=0; i<4; i++) vertices.push_back({0, (i&1 ? -phi:phi), (i&2 ? -inv_phi:inv_phi)});
    // (+-1/phi, 0, +-phi)
    for (int i=0; i<4; i++) vertices.push_back({(i&1 ? -inv_phi:inv_phi), 0, (i&2 ? -phi:phi)});
    // (+-phi, +-1/phi, 0)
    for (int i=0; i<4; i++) vertices.push_back({(i&1 ? -phi:phi), (i&2 ? -inv_phi:inv_phi), 0});

    double t0 = t_min, t1 = t_max;
    Math::Vector3D n0, n1;
    bool hit = true;
    
    // Normalize normals and compute d
    for (auto& n : normals) {
        n.normalize();
        double d = 0;
        for (const auto& v : vertices) {
            double val = n.dot(v);
            if (val > d) d = val;
        }
        
        // Scale distance by Scale Factor s
        // Effective Plane: dot(N, P) - d*s = 0.
        // Wait, if P is scaled by s, P_local = P/s.
        // dot(N, P/s) <= d => dot(N, P) <= d*s.
        double plane_d = -d * s; // Eq: dot(N, P) + plane_d <= 0 for inside?
        // Wait, standard: dot(N, P) = dist. Max dist is d*s.
        // So plane is at distance d*s along N.
        // Plane eq: N.P - d*s = 0 (pointing out?).
        // If N points out, then for inside point, dot(N, P) < d*s.
        // So numer = d*s - dot(N, O).
        
        double numer = (d * s) - n.dot(r_orig);
        double denom = n.dot(r_d);
        
        if (std::abs(denom) < 1e-9) { 
             // Ray parallel. If numer < 0, origin is outside (dist > d*s).
             // Wait, if dot(N, O) > d*s -> outside. numer < 0.
             if (numer < 0) { hit = false; break; }
        } else {
             double t = numer / denom;
             if (denom > 0) { // Exiting (Ray goes along normal)
                 if (t < t1) { t1 = t; n1 = n; }
             } else { // Entering
                 if (t > t0) { t0 = t; n0 = n; }
             }
             if (t0 > t1) { hit = false; break; }
        }
    }
    
    if (hit && t0 < t_max && t0 > t_min) {
        rec.t = t0;
        rec.point = r.at(t0);
        rec.normal = n0;
        rec.setFaceNormal(r, rec.normal);
        rec.material = material;
        return true;
    }

    return false;
}

void primitives::Dodecahedron::Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material)
{
    this->position = centre;
    this->radius = scale.x;
    this->material = material;
}

extern "C" primitives::IPrimitive *createDodecahedron()
{
    return new primitives::Dodecahedron();
}
