/*
** EPITECH PROJECT, 2025
** Torus
** File description:
** Torus primitive
*/
#include "Torus.hpp"
#include <cmath>
#include <algorithm>

primitives::Torus::Torus() 
    : position(0, 0, 0), majorRadius(1), minorRadius(0.3), material(nullptr)
{
}

primitives::Torus::~Torus() 
{
}

// Solve quartic equation for torus intersection
static int solveQuartic(double c[5], double s[4])
{
    double coeffs[4];
    double z, u, v, sub;
    double A, B, C, D;
    double sq_A, p, q, r;
    int i, num;

    A = c[3] / c[4];
    B = c[2] / c[4];
    C = c[1] / c[4];
    D = c[0] / c[4];

    sq_A = A * A;
    p = -3.0/8 * sq_A + B;
    q = 1.0/8 * sq_A * A - 1.0/2 * A * B + C;
    r = -3.0/256*sq_A*sq_A + 1.0/16*sq_A*B - 1.0/4*A*C + D;

    if (std::abs(r) < 1e-10) {
        coeffs[0] = q;
        coeffs[1] = p;
        coeffs[2] = 0;
        coeffs[3] = 1;
        // Solve cubic - simplified
        num = 0;
    } else {
        // Ferrari's solution - simplified approximation
        double disc = q*q/4 + p*p*p/27 - r;
        if (disc < 0) return 0;
        num = 0;
    }

    sub = 1.0/4 * A;
    for (i = 0; i < num; ++i)
        s[i] -= sub;
    return num;
}

bool primitives::Torus::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    // Transform ray to object space
    Math::Vector3D ray_origin = r.getOrigin() - position;
    Math::Vector3D ray_direction = r.getDirection();
    
    // Apply inverse rotation if needed
    if (rotation.x != 0 || rotation.y != 0 || rotation.z != 0) {
        Math::Vector3D inv_rotation = Math::Vector3D(-rotation.x, -rotation.y, -rotation.z);
        ray_origin = ray_origin.rotate(inv_rotation);
        ray_direction = ray_direction.rotate(inv_rotation);
    }
    
    double R = majorRadius; // Distance from center to tube center
    double r_tube = minorRadius; // Tube radius
    
    // Parametric torus equation leads to quartic
    // Using iterative ray marching for simpler implementation
    double t = t_min;
    double step = 0.05;
    
    while (t < t_max) {
        Math::Vector3D p = ray_origin + ray_direction * t;
        
        // Distance to torus surface
        double q = std::sqrt(p.x * p.x + p.z * p.z) - R;
        double dist = std::sqrt(q * q + p.y * p.y) - r_tube;
        
        if (dist < 0.001) {
            rec.t = t;
            rec.point = r.at(t);
            
            // Calculate normal in object space
            double len_xz = std::sqrt(p.x * p.x + p.z * p.z);
            Math::Vector3D normal_local;
            if (len_xz > 1e-6) {
                Math::Vector3D center_on_ring = Math::Vector3D(p.x / len_xz * R, 0, p.z / len_xz * R);
                normal_local = (p - center_on_ring).normalized();
            } else {
                normal_local = Math::Vector3D(0, 1, 0);
            }
            
            // Transform normal back to world space
            if (rotation.x != 0 || rotation.y != 0 || rotation.z != 0) {
                normal_local = normal_local.rotate(rotation);
            }
            
            rec.normal = normal_local.normalized();
            rec.setFaceNormal(r, rec.normal);
            rec.material = material;
            return true;
        }
        
        // Adaptive step size
        step = std::max(0.01, dist * 0.5);
        t += step;
    }
    
    return false;
}

void primitives::Torus::Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material)
{
    this->position = centre;
    this->majorRadius = scale.x;
    this->minorRadius = scale.y > 0 ? scale.y : scale.x * 0.3;
    this->material = material;
}

extern "C" primitives::IPrimitive *createTorus()
{
    return new primitives::Torus();
}
