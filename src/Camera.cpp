/*
** EPITECH PROJECT, 2025
** Camera
** File description:
** Camera
*/
#include "Camera.hpp"

RayTracer::Camera::Camera()
{
}

RayTracer::Camera::~Camera()
{
}

RayTracer::Camera::Camera(int width, int height, int x, int y, int z, int fov)
{
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    this->z = z;
    this->fov = fov;

    double aspect_ratio = static_cast<double>(width) / static_cast<double>(height);
    double theta = fov * M_PI / 180.0;
    double half_height = tan(theta / 2);
    double half_width = aspect_ratio * half_height;

    lower_left_corner = Math::Vector3D(-half_width, -half_height, -1.0);
    horizontal = Math::Vector3D(2 * half_width, 0.0, 0.0);
    vertical = Math::Vector3D(0.0, 2 * half_height, 0.0);
    origin = Math::Vector3D(x, y, z);
}

RayTracer::Ray RayTracer::Camera::ray(double u, double v) const
{
    return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
}
