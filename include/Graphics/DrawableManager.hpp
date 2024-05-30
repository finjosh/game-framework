#ifndef DRAWABLEMANAGER_H
#define DRAWABLEMANAGER_H

#pragma once

#include <set>

#include "SFML/Graphics/RenderWindow.hpp"

#include "DrawableObject.hpp"

class DrawableManager
{
public:
    /// @brief draws all drawable objs
    static void draw(sf::RenderWindow& window);
    static size_t getNumberOfObjects();

protected:
    static void addDrawable(DrawableObject* DrawableObject);
    static void removeDrawable(DrawableObject* DrawableObject);

    friend DrawableObject;

private:
    inline DrawableManager() = default;
    
    static std::set<DrawableObject*, _drawableComp> m_drawables;
};

#endif
