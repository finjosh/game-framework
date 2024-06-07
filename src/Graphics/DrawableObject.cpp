#include "Graphics/DrawableObject.hpp"
#include "Graphics/DrawableManager.hpp"

bool _drawableComp::operator() (const DrawableObject* lhs, const DrawableObject* rhs) const
{
    if (lhs->getDrawStage() < rhs->getDrawStage())
        return true;
    else if (lhs->getDrawStage() > rhs->getDrawStage())
        return false;
    else if (lhs->getLayer() <= rhs->getLayer() && lhs->getID() < rhs->getID())
        return true;
    else 
        return false;

//     if (lhs->getDrawStage() < rhs->getDrawStage() || (lhs->getDrawStage() == rhs->getDrawStage() && lhs->getLayer() <= rhs->getLayer()) && lhs->getID() < rhs->getID())
//         return true;
//     else    
//         return false;
}

DrawableObject::DrawableObject(int layer, DrawStage stage) : m_layer(layer), m_stage(stage)
{
    m_onParentRemoved(&DrawableObject::m_removeParent, this);
    m_onParentSet(&DrawableObject::m_setParent, this);

    DrawableManager::addDrawable(this);
}

DrawableObject::~DrawableObject()
{
    DrawableManager::removeDrawable(this);
}

void DrawableObject::setLayer(int layer)
{
    DrawableManager::removeDrawable(this);
    m_layer = layer;
    DrawableManager::addDrawable(this);
}

int DrawableObject::getLayer() const
{
    return m_layer;
}

void DrawableObject::setDrawStage(DrawStage stage)
{
    DrawableManager::removeDrawable(this);
    m_stage = stage;
    if (m_drawableParent)
        m_removeParent(); // also adds back to the drawable manager
    else
        DrawableManager::addDrawable(this);
}

DrawStage DrawableObject::getDrawStage() const
{
    if (m_drawableParent)
        return m_drawableParent->getDrawStage();
    else
        return m_stage;
}

void DrawableObject::m_setParent()
{
    auto curParent = this->getParent();
    DrawableObject* drawableParent = curParent->cast<DrawableObject>();

    while (drawableParent == nullptr && curParent != nullptr)
    {
        curParent = curParent->getParent();
        drawableParent = curParent->cast<DrawableObject>();
    }

    if (drawableParent != nullptr)
    {
        DrawableManager::removeDrawable(this);
        drawableParent->m_drawableChildren.insert({this});
        m_drawableParent = drawableParent;
    }
}

void DrawableObject::m_removeParent()
{
    m_drawableParent->m_drawableChildren.erase(this);
    m_drawableParent = nullptr;
    DrawableManager::addDrawable(this);
}

// TODO take in the parent position (either regular or interpolated)
// TODO make objects children store local instead of global position?
// TODO update all object functions to work with local instead of global?
void DrawableObject::m_draw(sf::RenderWindow& window) 
{
    this->Draw(window);
    for (auto child: m_drawableChildren)
    {
        child->m_draw(window);
    }
    this->LateDraw(window);
}
