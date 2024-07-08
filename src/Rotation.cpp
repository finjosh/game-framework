#include "Rotation.hpp"
#include "Vector2.hpp"
#include "math.h"

Rotation::Rotation(float radians) : cos(std::cos(radians)), sin(std::sin(radians)) {}

Rotation::Rotation(const Rotation& rotation) : cos(rotation.cos), sin(rotation.sin) {}

Rotation::Rotation(float cos, float sin) : cos(cos), sin(sin) {}

void Rotation::set(float radians)
{
    cos = std::cos(radians);
    sin = std::sin(radians);
}

float Rotation::getAngle() const
{
    return std::atan2(sin, cos);
}

float Rotation::getAngleInDegrees() const
{
    return std::atan2(sin, cos) * 180 / PI;
}

void Rotation::setZero()
{
    sin = 0.f;
    cos = 1.f;
}

Vector2 Rotation::GetXAxis() const
{
    return Vector2{cos, sin};
}

Vector2 Rotation::GetYAxis() const
{
    return Vector2{-sin, cos};
}

Rotation Rotation::operator + (Rotation rotation) const
{
    return {cos*rotation.cos - sin*rotation.sin, sin*rotation.cos + cos*rotation.sin};
}

void Rotation::operator += (Rotation rotation)
{
    float cosTemp = cos*rotation.cos - sin*rotation.sin;
    sin = sin*rotation.cos + cos*rotation.sin;
    cos = cosTemp;
}

Rotation Rotation::operator - (Rotation rotation) const
{
    return {cos*rotation.cos + sin*rotation.sin, sin*rotation.cos - cos*rotation.sin};
}

Rotation Rotation::operator - () const
{
    return {cos, -sin};
}

void Rotation::operator -= (Rotation rotation)
{
    float cosTemp = cos*rotation.cos + sin*rotation.sin;
    sin = sin*rotation.cos - cos*rotation.sin;
    cos = cosTemp;
}

void Rotation::operator = (Rotation rotation)
{
    cos = rotation.cos;
    sin = rotation.sin;
}
