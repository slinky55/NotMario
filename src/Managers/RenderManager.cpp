#include "Managers/RenderManager.h"

RenderManager::RenderManager(entt::registry& _reg,
                             sf::RenderWindow& _win)
                             :
                             m_reg(_reg),
                             m_window(_win)
{
    m_window.create(sf::VideoMode({800, 600}), "Hello");
    assert(m_window.isOpen());

    // TODO: Log that render system was started
}

// API

void RenderManager::Draw()
{
    m_window.clear();

    // TODO: Get view of render-able entities, and call their draw method

    m_window.display();
}
