/*
** EPITECH PROJECT, 2025
** Camera
** File description:
** Camera
*/
#ifndef CAMERA_HPP_
    #define CAMERA_HPP_
    #include <iostream>
    #include <cmath>
    #include <vector>
    #include "Primitives/Vector3D.hpp"
    #include "Ray.hpp"

namespace RayTracer {
    class Camera {
        public:
            Camera();
            ~Camera();
            Camera(int width, int height, int x, int y, int z, int fov);
            RayTracer::Ray ray(double u, double v) const;

            Math::Vector3D getOrigin() const { return origin; }
            Math::Vector3D getLowerLeftCorner() const { return lower_left_corner; }
            Math::Vector3D getHorizontal() const { return horizontal; }
            Math::Vector3D getVertical() const { return vertical; }
            int getWidth() const { return width; }
            int getHeight() const { return height; }
            int getFov() const { return fov; }
            int getX() const { return x; }
            int getY() const { return y; }
            int getZ() const { return z; }

        private:
            Math::Vector3D origin;
            Math::Vector3D lower_left_corner;
            Math::Vector3D horizontal;
            Math::Vector3D vertical;
            int width;
            int height;
            int fov;
            int x;
            int y;
            int z;
    };
}

#endif /* !CAMERA_HPP_ */
