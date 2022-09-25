#pragma once

#include <entt/entity/registry.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class InputManager
{
public:
    explicit InputManager(entt::registry& _reg);

    [[nodiscard]] static bool WindowDidClose(sf::RenderWindow& _window);
    void PollInput();
private:
    entt::registry& m_reg;
};