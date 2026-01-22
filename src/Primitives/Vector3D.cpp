/*
** EPITECH PROJECT, 2025
** Vector3D
** File description:
** Vector3D
*/
#include "Vector3D.hpp"

namespace Math {

Vector3D Vector3D::cross(const Vector3D& other) const
{
    return Vector3D(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

Vector3D Vector3D::normalized() const
{
    double len = length();
    if (len > 0)
        return Vector3D(x / len, y / len, z / len);
    return *this;
}

void Vector3D::normalize()
{
    double len = length();
    if (len > 0) {
        x /= len;
        y /= len;
        z /= len;
    }
}

Vector3D Vector3D::operator+(const Vector3D& other) const
{
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D Vector3D::operator-(const Vector3D& other) const
{
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

Vector3D Vector3D::operator*(const Vector3D& other) const
{
    return Vector3D(x * other.x, y * other.y, z * other.z);
}

Vector3D Vector3D::operator/(const Vector3D& other) const
{
    return Vector3D(x / other.x, y / other.y, z / other.z);
}

bool Vector3D::operator==(const Vector3D& other) const
{
    return (x == other.x && y == other.y && z == other.z);
}

bool Vector3D::operator!=(const Vector3D& other) const
{
    return !(*this == other);
}

bool Vector3D::operator<(const Vector3D& other) const
{
    return length() < other.length();
}

bool Vector3D::operator>(const Vector3D& other) const
{
    return length() > other.length();
}

bool Vector3D::operator<=(const Vector3D& other) const
{
    return length() <= other.length();
}

bool Vector3D::operator>=(const Vector3D& other) const
{
    return length() >= other.length();
}

Vector3D& Vector3D::operator+=(const Vector3D& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3D& Vector3D::operator*=(const Vector3D& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

Vector3D& Vector3D::operator/=(const Vector3D& other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
}

Vector3D Vector3D::operator*(double scalar) const
{
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

Vector3D Vector3D::operator/(double scalar) const
{
    return Vector3D(x / scalar, y / scalar, z / scalar);
}

Vector3D& Vector3D::operator*=(double scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3D& Vector3D::operator/=(double scalar)
{
    double invScalar = 1.0 / scalar;
    x *= invScalar;
    y *= invScalar;
    z *= invScalar;
    return *this;
}

Vector3D Vector3D::reflect(const Vector3D& incident, const Vector3D& normal)
{
    return incident - normal * 2.0 * incident.dot(normal);
}

Vector3D operator*(double scalar, const Vector3D& v)
{
    return v * scalar;
}

std::ostream& operator<<(std::ostream& os, const Vector3D& v)
{
    os << v.x << " " << v.y << " " << v.z;
    return os;
}

std::istream& operator>>(std::istream& is, Vector3D& v)
{
    is >> v.x >> v.y >> v.z;
    return is;
}

Vector3D Vector3D::rotateX(double angle) const
{
    double rad = angle * M_PI / 180.0;
    double c = std::cos(rad);
    double s = std::sin(rad);
    return Vector3D(x, y * c - z * s, y * s + z * c);
}

Vector3D Vector3D::rotateY(double angle) const
{
    double rad = angle * M_PI / 180.0;
    double c = std::cos(rad);
    double s = std::sin(rad);
    return Vector3D(x * c + z * s, y, -x * s + z * c);
}

Vector3D Vector3D::rotateZ(double angle) const
{
    double rad = angle * M_PI / 180.0;
    double c = std::cos(rad);
    double s = std::sin(rad);
    return Vector3D(x * c - y * s, x * s + y * c, z);
}

Vector3D Vector3D::rotate(const Vector3D& angles) const
{
    return rotateX(angles.x).rotateY(angles.y).rotateZ(angles.z);
}

} // namespace Math