#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entity/registry.hpp>

#include "Components/SpriteC.h"
#include "Components/RectangleC.h"

class RenderManager
{
public:
    RenderManager(entt::registry& _reg,
                  sf::RenderWindow& _win);

    void Draw();
private:
    sf::RenderWindow& m_window;
    entt::registry& m_reg;
};