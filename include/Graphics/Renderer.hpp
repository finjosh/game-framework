#ifndef RENDERER_H
#define RENDERER_H

#pragma once

#include "SFML/Graphics/Shape.hpp"

#include "Object.hpp"
#include "Settings.hpp"
#include "Graphics/DrawableObject.hpp"
// #include "Physics/WorldHandler.hpp"

// TODO make renderers for other sfml drawables

/// @brief renderer for any sf::Shape
/// @warning if derived from do NOT forget to use "createDestroy()"
/// @note this can be used as a stand alone object
/// @tparam T the wanted sf::Shape to render
template <typename T, typename std::enable_if_t<std::is_base_of<sf::Shape, T>::value>* = nullptr>
class Renderer : public virtual Object, public DrawableObject, public T
{
public:
    using Ptr = Object::Ptr<Renderer<T>>;

    inline Renderer()
    {
        T::setScale(PIXELS_PER_METER, PIXELS_PER_METER);
    }

    using Object::setPosition;
    using Object::getPosition;
    using Object::setRotation;
    using Object::getRotation;
    using Object::setTransform;
    using Object::getTransform;
    using Object::move;
    using Object::rotate;

    inline void setScale(float x, float y)
    {
        T::setScale(PIXELS_PER_METER * x, PIXELS_PER_METER * y);
    }

    inline Vector2 getScale() const
    {
        Vector2 temp = T::getScale();
        temp /= PIXELS_PER_METER;
        return temp;
    }

protected:
    inline void Draw(sf::RenderTarget* target, const Transform& thisTransform) override
    {
        // T::setPosition((sf::Vector2f)Object::getGlobalPosition()*PIXELS_PER_METER);
        // T::setRotation(Object::getGlobalRotation().getAngle()*180/PI);
        T::setPosition((sf::Vector2f)thisTransform.position*PIXELS_PER_METER);
        T::setRotation(thisTransform.rotation.getAngle()*180/PI);
        target->draw(*this);
    }

private:
    float m_xScale = 1, m_yScale = 1;

    using T::setScale;
    using T::getScale;
    using T::scale;

    createDestroy();
};

#endif
