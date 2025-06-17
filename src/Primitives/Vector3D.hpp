/*
** EPITECH PROJECT, 2025
** Vector3D
** File description:
** Vector3D
*/
#ifndef VECTOR3D_HPP_
    #define VECTOR3D_HPP_

    #include <cmath>
    #include <iostream>

namespace Math {

class Vector3D {
public:
    // Constructeurs/destructeur
    Vector3D() : x(0), y(0), z(0) {}
    Vector3D(double a, double b, double c) : x(a), y(b), z(c) {}
    ~Vector3D() = default;
    
    // Accesseurs
    inline double getX() const { return x; }
    inline double getY() const { return y; }
    inline double getZ() const { return z; }
    
    // Méthodes de calcul
    double length() const { return std::sqrt(x * x + y * y + z * z); }
    double dot(const Vector3D& other) const { return x * other.x + y * other.y + z * other.z; }
    Vector3D cross(const Vector3D& other) const;
    Vector3D normalized() const;
    void normalize();
    double lengthSquared() const { return x * x + y * y + z * z; }
        
    // Opérateurs arithmétiques
    Vector3D operator+(const Vector3D& other) const;
    Vector3D operator-(const Vector3D& other) const;
    Vector3D operator*(const Vector3D& other) const;
    Vector3D operator/(const Vector3D& other) const;
    Vector3D operator-() const { return Vector3D(-x, -y, -z); }
    
    // Opérateurs de comparaison
    bool operator==(const Vector3D& other) const;
    bool operator!=(const Vector3D& other) const;
    bool operator<(const Vector3D& other) const;
    bool operator>(const Vector3D& other) const;
    bool operator<=(const Vector3D& other) const;
    bool operator>=(const Vector3D& other) const;
    
    // Opérateurs d'affectation composée
    Vector3D& operator+=(const Vector3D& other);
    Vector3D& operator-=(const Vector3D& other);
    Vector3D& operator*=(const Vector3D& other);
    Vector3D& operator/=(const Vector3D& other);
    
    // Opérateurs scalaires
    Vector3D operator*(double scalar) const;
    Vector3D operator/(double scalar) const;
    Vector3D& operator*=(double scalar);
    Vector3D& operator/=(double scalar);
    
    // Réflexion
    static Vector3D reflect(const Vector3D& incident, const Vector3D& normal);
    
    // Variables membres
    double x, y, z;
};

// Opérateurs externes
Vector3D operator*(double scalar, const Vector3D& v);

// Fonctions d'entrée/sortie
std::ostream& operator<<(std::ostream& os, const Vector3D& v);
std::istream& operator>>(std::istream& is, Vector3D& v);

}

#endif /* !VECTOR3D_HPP_ */
