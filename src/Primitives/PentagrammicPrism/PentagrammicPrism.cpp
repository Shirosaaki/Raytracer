/*
** EPITECH PROJECT, 2025
** PentagrammicPrism
** File description:
** PentagrammicPrism primitive
*/
#include "PentagrammicPrism.hpp"
#include <cmath>
#include <vector>

primitives::PentagrammicPrism::PentagrammicPrism() 
    : position(0, 0, 0), scale(1, 1, 1), material(nullptr)
{
}

primitives::PentagrammicPrism::~PentagrammicPrism() 
{
}

// Function to check if point is inside a polygon
static bool pointInPolygon(const Math::Vector3D& p, const std::vector<std::pair<double, double>>& poly) {
    bool inside = false;
    size_t j = poly.size() - 1;
    for (size_t i = 0; i < poly.size(); i++) {
        if ((poly[i].second > p.z) != (poly[j].second > p.z) &&
            (p.x < (poly[j].first - poly[i].first) * (p.z - poly[i].second) / (poly[j].second - poly[i].second) + poly[i].first)) {
            inside = !inside;
        }
        j = i;
    }
    return inside;
}

bool primitives::PentagrammicPrism::hit(const RayTracer::Ray& r, double t_min, double t_max, HitRecord &rec) const
{
    // Check Y-slab intersection first
    Math::Vector3D r_orig = r.getOrigin() - position;
    Math::Vector3D r_d = r.getDirection();
    
    // Apply inverse rotation to ray if needed
    if (rotation.x != 0 || rotation.y != 0 || rotation.z != 0) {
        Math::Vector3D inv_rotation = Math::Vector3D(-rotation.x, -rotation.y, -rotation.z);
        r_orig = r_orig.rotate(inv_rotation);
        r_d = r_d.rotate(inv_rotation);
    }
    double height = scale.y;
    double t_enter = t_min;
    double t_exit = t_max;
    
    double radius = scale.x;
    double inner_radius = radius * 0.382; // standard pentagram ratio
    
    std::vector<std::pair<double, double>> vertices;
    for (int i = 0; i < 10; ++i) {
        double angle = i * M_PI / 5.0 - M_PI / 2.0;
        double r_p = (i % 2 == 0) ? radius : inner_radius;
        vertices.push_back({r_p * cos(angle), r_p * sin(angle)});
    }
    
    // Check slabs (Y)
    double y_min = -height/2; 
    double y_max = height/2;
    double t_y1 = (y_min - r_orig.y) / r_d.y;
    double t_y2 = (y_max - r_orig.y) / r_d.y;
    if (t_y1 > t_y2) std::swap(t_y1, t_y2);
    
    double t_near = std::max(t_min, t_y1);
    double t_far = std::min(t_max, t_y2);
    if (t_near > t_far) return false;
    
    // Bounding Cylinder optimization
    double a = r_d.x * r_d.x + r_d.z * r_d.z;
    double b = 2 * (r_orig.x * r_d.x + r_orig.z * r_d.z);
    double c = r_orig.x * r_orig.x + r_orig.z * r_orig.z - radius * radius;
    double disc = b*b - 4*a*c;
    if (disc < 0) return false;
    
    double best_t = t_max + 1;
    bool found = false;
    Math::Vector3D norm;
    
    // Check caps
    if (std::abs(r_d.y) > 1e-6) {
        for (int k = 0; k < 2; k++) {
            double y = (k==0) ? y_min : y_max;
            double t = (y - r_orig.y) / r_d.y;
            if (t > t_min && t < best_t) {
                Math::Vector3D p = r_orig + r_d * t;
                if (pointInPolygon(p, vertices)) {
                    best_t = t;
                    found = true;
                    norm = Math::Vector3D(0, (k==0)? -1 : 1, 0);
                }
            }
        }
    }
    
    // Check Walls
    for (int i = 0; i < 10; ++i) {
        std::pair<double,double> p1 = vertices[i];
        std::pair<double,double> p2 = vertices[(i+1)%10];
        
        double dx = p2.first - p1.first;
        double dz = p2.second - p1.second;
        Math::Vector3D wall_normal(dz, 0, -dx);
        wall_normal.normalize();
        
        double d = wall_normal.x * p1.first + wall_normal.z * p1.second;
        
        double denom = r_d.dot(wall_normal);
        if (std::abs(denom) > 1e-6) {
            double t = (d - r_orig.dot(wall_normal)) / denom;
            if (t > t_min && t < best_t) {
                Math::Vector3D hitp = r_orig + r_d * t;
                if (hitp.y >= y_min && hitp.y <= y_max) {
                    double l2 = dx*dx + dz*dz;
                    if (l2 > 1e-9) {
                        double proj = ((hitp.x - p1.first)*dx + (hitp.z - p1.second)*dz) / l2;
                        if (proj >= 0 && proj <= 1) {
                             best_t = t;
                             found = true;
                             norm = wall_normal;
                        }
                    }
                }
            }
        }
    }
    
    if (found) {
        rec.t = best_t;
        rec.point = r.at(best_t);
        
        // Transform normal back to world space
        if (rotation.x != 0 || rotation.y != 0 || rotation.z != 0) {
            norm = norm.rotate(rotation);
        }
        
        rec.normal = norm;
        rec.setFaceNormal(r, rec.normal);
        rec.material = material;
        return true;
    }
    
    return false;
}

void primitives::PentagrammicPrism::Init(Math::Vector3D centre, Math::Vector3D scale, RayTracer::IMaterials *material)
{
    this->position = centre;
    this->scale = scale;
    this->material = material;
}

extern "C" primitives::IPrimitive *createPentagrammicPrism()
{
    return new primitives::PentagrammicPrism();
}
