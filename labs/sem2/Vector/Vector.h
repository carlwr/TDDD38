#pragma once
#include <iostream>

// Declare your class here

class Vector
{
public:
    Vector(double x, double y);

    Vector& operator+=(const Vector);
    Vector& operator-=(const Vector);
    Vector& operator*=(double k);
    Vector& operator/=(double k);

    Vector operator-() const;

    bool operator==(Vector const& v) const;
    bool operator!=(Vector const& v) const;

    Vector operator*(Vector const& rhs) const;

    double length() const;

    friend std::ostream& operator<<(std::ostream& os, Vector const& other);


    friend std::istream& operator>>(std::istream& is, Vector& other);

private:
    double x, y;
};

Vector operator*(Vector const& lhs, double rhs);
Vector operator*(double rhs, Vector const& lhs);
Vector operator+(Vector const&  lhs, Vector const& rhs);
Vector operator-(Vector const&  lhs, Vector const& rhs);
