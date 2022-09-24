#include "Managers/RenderManager.h"

RenderManager::RenderManager(entt::registry& _reg,
                             sf::RenderWindow& _win)
                             :
                             m_reg(_reg),
                             m_window(_win)
{
}

// API

void RenderManager::OnInit()
{
    m_window.create(sf::VideoMode({800, 600}), "Hello");
    assert(m_window.isOpen());

    // TODO: Log that render system was started
}

void RenderManager::Draw()
{
    m_window.clear();

    // TODO: Get view of render-able entities, and call their draw method
    auto view = m_reg.view<RenderableC>();

    for (auto entity : view)
    {
        auto& renderable = m_reg.get<RenderableC>(entity);
        m_window.draw(*renderable.drawable);
    }

    m_window.display();
}
