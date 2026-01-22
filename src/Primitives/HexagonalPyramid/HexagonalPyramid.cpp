/*
** EPITECH PROJECT, 2025
** HexagonalPyramid
** File description:
** HexagonalPyramid primitive
*/
#include "HexagonalPyramid.hpp"
#include <cmath>
#include <vector>
#include <algorithm>

primitives::HexagonalPyramid::HexagonalPyramid() 
    : position(0, 0, 0), scale(1, 1, 1), material(nullptr)
{
}

primitives::HexagonalPyramid::~HexagonalPyramid() 
{
}

bool primitives::HexagonalPyramid::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    // Hexagonal Pyramid: Base (hexagon) on XZ plane? Or centered at Y=0?
    // Let's assume height is along Y. Base at Y = -height/2, Tip at Y = height/2.
    // Or Base at Y=0, Tip at Y=height.
    // Let's stick to Centered Origin for primitives usually.
    // Base at Y = -scale.y/2, Tip at Y = scale.y/2.
    
    Math::Vector3D r_orig = r.getOrigin() - position;
    Math::Vector3D r_d = r.getDirection();
    double h = scale.y;
    double radius = scale.x; // radius of hexagonal base
    
    double y_base = -h/2.0;
    double y_tip = h/2.0;
    
    double t_enter = t_min;
    double t_exit = t_max;
    Math::Vector3D n_enter, n_exit;
    
    // 1. Base Plane (Y = y_base)
    // Intersection with the plane, check if inside hexagon.
    // But easier: treat as Intersection of Half-Spaces (Convex Polyhedron).
    
    // Base Plane: Normal (0, -1, 0), Point (0, y_base, 0) -> y >= y_base
    // But for the closed volume, we want to be *above* base.
    // Plane eq: (P - P0) . N <= 0 for "inside"? Or hit logic.
    // Let's use the slab method (Kay-Kajiya) for convex shapes.
    
    // Planar equations: N . P + d = 0.
    // We want intersection of:
    // 1. y >= y_base  => Plane N=(0,-1,0), d=y_base ?? 
    //    Plane eq: y - y_base = 0. Inward Normal (0,1,0).
    //    Let's align normals OUTWARD.
    //    Base: Normal (0, -1, 0), Point (0, y_base, 0) => P.y <= y_base is outside?
    //    Plane: Y = y_base. Normal (0, -1, 0). Dist from origin? 
    //    Eq: 0*x + (-1)*y + 0*z + d = 0.  -y_base + d = 0 => d = y_base.
    //    => -y + y_base = 0. check origin(0,0,0) -> y_base. If y_base < 0, origin inside.
    
    struct Plane { Math::Vector3D n; double d; }; 
    std::vector<Plane> planes;
    
    // Base
    planes.push_back({ {0, -1, 0}, y_base }); // N=(0,-1,0), d=y_base. -y + y_base = 0 ? No.
    // Dist from origin to plane along normal.
    // Plane eq: N.P = -d (or d depending on convention).
    // Standard: dot(N, P) + d = 0.
    // Base: y = y_base. dot((0,-1,0), (x,y,z)) = -y.  -y + y_base = 0 ??
    // If y = y_base, -y_base + y_base = 0.
    // Point (0,0,0) -> 0 + y_base. If y_base = -1, val = -1 (Inside). 
    // Wait, let's use standard slab method:
    // For each plane, calculate t_near and t_far.
    // Denom = dot(N, D). Numer = -(dot(N, O) + d).
    
    // Planes:
    // Base: N=(0,-1,0), Point=(0, y_base, 0). d = -dot(N, P) = -(-y_base) = y_base.
    planes.push_back({ {0, -1, 0}, y_base });
    
    // 6 Side Faces.
    // Tip at (0, y_tip, 0).
    // Base vertices at y_base.
    // Hexagon vertices: (R*cos(i*60), y_base, R*sin(i*60))
    for (int i = 0; i < 6; ++i) {
        double angle1 = i * M_PI / 3.0;
        double angle2 = (i + 1) * M_PI / 3.0;
        Math::Vector3D p1(radius * cos(angle1), y_base, radius * sin(angle1));
        Math::Vector3D p2(radius * cos(angle2), y_base, radius * sin(angle2));
        Math::Vector3D tip(0, y_tip, 0);
        
        // Normal of the triangle (p1, p2, tip)
        Math::Vector3D edge1 = p2 - p1;
        Math::Vector3D edge2 = tip - p1;
        Math::Vector3D normal = edge1.cross(edge2);
        normal.normalize();
        
        double d = -normal.dot(p1); // Plane eq constant
        planes.push_back({normal, d});
    }

    double t0 = t_min, t1 = t_max;
    Math::Vector3D n0, n1;
    bool hit = true;
    
    // Generic Convex Polyhedron Intersection
    for (const auto& p : planes) {
        double numer = -(p.n.dot(r_orig) + p.d);
        double denom = p.n.dot(r_d);
        
        if (std::abs(denom) < 1e-9) {
            // Ray parallel to plane
            if (numer < 0) { // Origin outside
                hit = false; 
                break; 
            }
        } else {
            double t = numer / denom;
            if (denom > 0) { // Exiting
                if (t < t1) { t1 = t; n1 = p.n; }
            } else { // Entering
                if (t > t0) { t0 = t; n0 = p.n; }
            }
            if (t0 > t1) {
                hit = false;
                break;
            }
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
