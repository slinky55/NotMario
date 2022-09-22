#include <RenderManager.h>

RenderManager::RenderManager()
{
    m_window.create(sf::VideoMode({800, 600}), "Hello");
    assert(m_window.isOpen());

    // TODO: Log that render system was started
}

// API

void RenderManager::Tick(const entt::registry &_reg)
{
    m_window.clear();

    // TODO: Get view of render-able entities, and call their draw method

    m_window.display();
}

// Accessors

sf::RenderWindow& RenderManager::Window() { return m_window; }
