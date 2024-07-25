#ifndef ROTATION_HPP
#define ROTATION_HPP

#pragma once

// #include "Box2D/b2_math.h" (B2_MATH_H)

#ifndef PI
#define PI 3.14159265358979323846f
#endif

class Vector2;

/// @note if you want helper functions to work with tgui, sfml, and box2d vectors make sure to include them before include "Vector2"
/// @note if you want the to string function to be defined include this the string include
class Rotation
{
public:
    inline Rotation() = default;
    Rotation(float radians);
    Rotation(const Rotation& rotation);
    Rotation(float cos, float sin);

    /// @brief sets the stored sin and cos values with and angle in radians
    void set(float radians);
    /// @returns the rotation/angle in radians
    float getAngle() const;
    /// @returns the rotation/angle in degrees
    float getAngleInDegrees() const;
    /// @brief sets the stored rotation to 0
    void setZero();
	/// @returns the rotated x axis (1,0) in terms of this rotation
	Vector2 GetXAxis() const;
    /// @returns the rotated y axis (0,1) in terms of this rotation
	Vector2 GetYAxis() const;

    //* box2d functions
    #ifdef B2_MATH_H
    inline Rotation(b2Rot rot) : cos(rot.c), sin(rot.s) {}
    explicit inline operator b2Rot() const
    {
        b2Rot temp;
        temp.c = cos;
        temp.s = sin;
        return temp;
    }
    #endif
    // ----------------

    //* string conversion function
    #ifdef _BASIC_STRING_H
    /// @note this calculates the angle and converts to a string
    inline std::basic_string<char> toString()
    {
        return std::to_string(this->getAngle());
    }
    /// @brief returns this rotation in degrees as a string
    /// @note this calculates the angle and converts to a string
    inline std::basic_string<char> toStringDegrees()
    {
        return std::to_string(this->getAngle() * 180 / PI);
    }
    #endif
    // ----------------

    Rotation operator + (Rotation rotation) const;
    void operator += (Rotation rotation);
    Rotation operator - (Rotation rotation) const;
    Rotation operator - () const;
    void operator -= (Rotation rotation);
    void operator = (Rotation rotation);

    float sin = 0.f, cos = 1.f;
protected:

private:

};

#endif
