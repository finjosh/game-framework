#ifndef COLOR_HPP
#define COLOR_HPP

#pragma once

#include <cstdint>

class Color
{
public:
    Color(uint8_t r = 255, uint8_t g = 255, uint8_t b = 255, uint8_t a = 255);
    bool operator==(const Color& rhs) const;
    bool operator!=(const Color& right) const;
    /// @brief computes the operation component wise (r,g,b,a)
    Color operator + (const Color& color) const;
    /// @brief computes the operation component wise (r,g,b,a)
    void operator += (const Color& color);
    /// @brief computes the operation component wise (r,g,b,a)
    Color operator - (const Color& color) const;
    /// @brief computes the operation component wise (r,g,b,a)
    void operator -= (const Color& color);
    /// @brief computes the operation component wise (r,g,b,a)
    Color operator * (const Color& color) const;
    /// @brief computes the operation component wise (r,g,b,a)
    void operator *= (const Color& color);
    /// @brief computes the operation component wise (r,g,b,a)
    Color operator / (const Color& color) const;
    /// @brief computes the operation component wise (r,g,b,a)
    void operator /= (const Color& color);
    /// @brief computer the operation on each component using the given scaler
    /// @note the result is casted to a uint8_t
    Color operator * (float scaler) const;
    /// @brief computer the operation on each component using the given scaler
    /// @note the result is casted to a uint8_t
    void operator *= (float scaler);
    /// @brief computer the operation on each component using the given scaler
    /// @note the result is casted to a uint8_t
    Color operator / (float scaler) const;
    /// @brief computer the operation on each component using the given scaler
    /// @note the result is casted to a uint8_t
    void operator /= (float scaler);

    //* SFML
    #ifdef SFML_COLOR_HPP
     /// @note you MUST include the sfml Color header BEFORE including this Color header
    inline Vector2(const sf::Color& color) : r(color.r), g(color.g), b(color.b), a(color.a) {}
    /// @returns the equivalent sf::Color
    explicit inline operator sf::Color() const
    {
        return sf::Color{r,g,b,a};
    } 
    #endif

    //* TGUI
    #ifdef TGUI_COLOR_HPP
     /// @note you MUST include the TGUI Color header BEFORE including this Color header
    inline Vector2(const tgui::Color& color) : r(color.r), g(color.g), b(color.b), a(color.a) {}
    /// @returns the equivalent tgui::Color
    explicit inline operator tgui::Color() const
    {
        return tgui::Color{r,g,b,a};
    } 
    #endif

    uint8_t r = 255, g = 255, b = 255, a = 255;
protected:

private:

};

#endif
