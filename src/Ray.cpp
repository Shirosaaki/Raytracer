/*
** EPITECH PROJECT, 2025
** Ray
** File description:
** Ray
*/
#include "Ray.hpp"

RayTracer::Ray::Ray()
{
    this->origin = Math::Vector3D(0, 0, 0);
    this->direction = Math::Vector3D(0, 0, 0);
}

RayTracer::Ray::~Ray()
{
}

RayTracer::Ray::Ray(const Math::Vector3D& origin, const Math::Vector3D& direction)
{
    this->origin = origin;
    this->direction = direction;
}
