#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entity/registry.hpp>

class RenderManager
{
public:
    RenderManager();

    void Tick(const entt::registry& _reg);

    sf::RenderWindow& Window();
private:
    sf::RenderWindow m_window;
};