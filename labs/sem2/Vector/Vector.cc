#include "Vector.h"

// implement all the functions declared in Vector.h here


Vector::Vector(double x = 0.0 , double y = 0.0): x{x}, y{y}
{
}

Vector& Vector::operator+=(const Vector v){
    x += v.x;
    y += v.y;
    return *this;
}

Vector& Vector::operator-=(const Vector v){
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector Vector::operator*(float f){
    return Vector(x * f, y * f);
}


Vector Vector::operator/(float f){
    return Vector(x / f, y / f);
}

std::ostream& Vector::operator<<(std::ostream& os){
    os <<"(" << x << ", " << y <<")";
}

std::istream& Vector::operator>>(std::istream& is){
    
}



Vector operator+(const Vector& lhs, const Vector& rhs ){
    return Vector(lhs)+= rhs;
}

Vector operator-(const Vector& lhs, const Vector& rhs ){
    return Vector(lhs)-= rhs;
}

Vector operator*(const Vector& lhs, const Vector& rhs ){
}