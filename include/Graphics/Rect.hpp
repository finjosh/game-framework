#ifndef RECT_H
#define RECT_H

#pragma once

#include "SFML/Graphics/RectangleShape.hpp"

#include "Object.hpp"
#include "Graphics/DrawableObject.hpp"
#include "Physics/WorldHandler.hpp"

class Rect : public virtual Object, public DrawableObject, public virtual sf::RectangleShape
{
public:
    using Object::setPosition;

protected:
    inline virtual void Draw(sf::RenderWindow& window) override
    {
        RectangleShape::setPosition(Object::getPosition().x*PIXELS_PER_METER, Object::getPosition().y*PIXELS_PER_METER);
        RectangleShape::setRotation(Object::getRotation()*180/PI);
        window.draw(*this);
    }

private:
    using sf::RectangleShape::setPosition;

};

#endif