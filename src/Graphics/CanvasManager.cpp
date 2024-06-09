#include "Graphics/CanvasManager.hpp"
#include "Graphics/WindowHandler.hpp"
#include "Graphics/CameraManager.hpp"

tgui::Gui CanvasManager::m_gui;
std::set<Canvas*, _drawableComp> CanvasManager::m_canvases;

void CanvasManager::initGUI()
{
    m_gui.setWindow(*WindowHandler::getRenderWindow());
    // auto temp = tgui::Group::create({std::numeric_limits<float>().max(), std::numeric_limits<float>().max()});
    // temp->setOrigin(std::numeric_limits<float>().max()/2, std::numeric_limits<float>().max()/2);
    // m_gui.add(temp);
}

void CanvasManager::handleEvent(sf::Event event)
{
    b2Vec2 screenPosition; // left, top in pixels
    if (auto camera = CameraManager::getMainCamera())
    {
        screenPosition = camera->getPosition();
        screenPosition *= PIXELS_PER_METER;
        screenPosition.x -= (float)m_gui.getWindow()->getSize().x/2;
        screenPosition.y -= (float)m_gui.getWindow()->getSize().y/2;
    }
    else
        screenPosition = {0,0};

    // first update all screen space canvases to have the proper position for events to be handled
    for (auto canvas: m_canvases)
    {
        // if (!canvas->isScreenSpace())
        // {
        //     if (CameraManager::getMainCamera()->isRotationLocked())
        //         continue;
        //     canvas->getGroup()->setRotation(CameraManager::getMainCamera()->getRotation()*180/PI);
        //     continue;
        // }

        const tgui::Vector2f origin = {canvas->getOrigin().x * canvas->getSize().x, canvas->getOrigin().y * canvas->getSize().y};
        canvas->getGroup()->setPosition(screenPosition.x + origin.x, screenPosition.y + origin.y);
    }

    // setting the viewport so mouse position events are updated properly
    m_gui.setAbsoluteView(tgui::FloatRect{screenPosition.x,screenPosition.y,(float)m_gui.getWindow()->getSize().x,(float)m_gui.getWindow()->getSize().y}); // setting the viewport so mouse position events are updated properly
    m_gui.setRelativeViewport(tgui::FloatRect{0,0,1,1});
    m_gui.handleEvent(event);
}

tgui::Gui& CanvasManager::getGui()
{
    return m_gui;
}

void CanvasManager::addCanvas(Canvas* canvas)
{
    m_canvases.insert(canvas);
}

void CanvasManager::removeCanvas(Canvas* canvas)
{
    m_canvases.erase(canvas);
}

void CanvasManager::drawOverlayGUI()
{
    if (!m_gui.getTarget() || (m_gui.getWindow()->getSize().x == 0) || (m_gui.getWindow()->getSize().y == 0) || (m_gui.getView().getWidth() <= 0) || (m_gui.getView().getHeight() <= 0))
        return;

    m_gui.setAbsoluteView(tgui::FloatRect{0,0,(float)m_gui.getWindow()->getSize().x,(float)m_gui.getWindow()->getSize().y});
    m_gui.setRelativeViewport(tgui::FloatRect{0,0,1,1});
    
    // Draw the canvases
    for (auto canvas: m_canvases)
    {
        if (canvas->isEnabled())
            canvas->Draw(m_gui.getTarget());
    }

    m_gui.updateTime();
}

void CanvasManager::updateViewForCamera(Camera* camera)
{
    m_gui.setAbsoluteView(tgui::FloatRect{(camera->getPosition().x-camera->getSize().x/2)*PIXELS_PER_METER, (camera->getPosition().y-camera->getSize().y/2)*PIXELS_PER_METER, camera->getSize().x*PIXELS_PER_METER, camera->getSize().y*PIXELS_PER_METER});
    auto temp = camera->getScreenRect();
    m_gui.setRelativeViewport(tgui::FloatRect{temp.left, temp.top, temp.width, temp.height});
}
