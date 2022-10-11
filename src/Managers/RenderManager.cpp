#include "Managers/RenderManager.h"

RenderManager::RenderManager(entt::registry& _reg,
                             sf::RenderWindow& _win)
                             :
                             m_reg(_reg),
                             m_window(_win)
{
}

// API

void RenderManager::Draw()
{
    m_window.clear({135, 206, 235});

    // TODO: Get view of render-able entities, and call their draw method
    auto sprites = m_reg.view<SpriteC>();
    auto rectShapes = m_reg.view<RectangleC>();

    for (auto& entity : sprites)
    {
        auto& sprite = m_reg.get<SpriteC>(entity);
        m_window.draw(sprite.sprite);
    }

    for (auto& entity : rectShapes)
    {
        auto& rectShape = m_reg.get<RectangleC>(entity);
        m_window.draw(rectShape.rect);
    }

    m_window.display();
}
