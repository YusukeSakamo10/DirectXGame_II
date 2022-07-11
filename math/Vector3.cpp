#include "Vector3.h"


#include <cmath>

Vector3::Vector3()
    :x(0),
    y(0),
    z(0)
{}

Vector3::Vector3(float x, float y, float z)
    : x(x),
    y(y),
    z(z)
{}

float Vector3::length() const
{
    float length_ = sqrt((x * x + y * y + z * z));
    return length_;
}

Vector3& Vector3::normalize()
{
    float Length = length();
    Vector3 Norm = { x / Length, y / Length, z / Length };

    return Norm;
}

float Vector3::dot(const Vector3& v) const
{
    return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::cross(const Vector3& v) const
{
    Vector3 cross_;
    cross_.x = y * v.z - z * v.y;
    cross_.y = z * v.x - x * v.z;
    cross_.z = x * v.y - y * v.x;
    return cross_;
}

Vector3 Vector3::operator+() const
{
    return *this;
}

Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

Vector3& Vector3::operator+=(const Vector3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

Vector3& Vector3::operator*=(float s)
{
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

Vector3& Vector3::operator/=(float s)
{
    x /= s;
    y /= s;
    z /= s;
    return *this;
}



const Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
    Vector3 temp(v1);
    temp += v2;
    return temp;
}

const Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
    Vector3 temp(v1);
    temp -= v2;
    return temp;
}

const Vector3 operator*(const Vector3& v, float s)
{
    Vector3 temp;
    temp.x = v.x * s;
    temp.y = v.y * s;
    temp.z = v.z * s;
    return temp;
}

const Vector3 operator*(float s, const Vector3& v)
{
    Vector3 temp;
    temp.x = s * v.x;
    temp.y = s * v.y;
    temp.z = s * v.z;
    return temp;
}

const Vector3 operator/(const Vector3& v, float s)
{
    return Vector3(v.x / s, v.y / s, v.z / s);
}
