/*
** EPITECH PROJECT, 2025
** Ray
** File description:
** Ray
*/
#ifndef RAY_HPP_
    #define RAY_HPP_
    #include <iostream>
    #include <cmath>
    #include <vector>
    #include "Primitives/Vector3D.hpp"

namespace RayTracer {
    class Ray {
        public:
            Ray();
            Ray(const Math::Vector3D& orig, const Math::Vector3D& dir);
            ~Ray();

            Math::Vector3D getOrigin() const { return origin; }
            Math::Vector3D getDirection() const { return direction; }
            Math::Vector3D at(double t) const {
                return origin + t * direction;
            }

            Math::Vector3D origin;
            Math::Vector3D direction;
    };
}

#endif /* !RAY_HPP_ */