#include "Managers/InputManager.h"

InputManager::InputManager(entt::registry &_reg)
:
m_reg(_reg)
{
}

bool InputManager::WindowDidClose(sf::RenderWindow& _window)
{
    sf::Event e{};
    while (_window.pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
        {
            _window.close();
            return true;
        }
    }
    return false;
}

void InputManager::PollInput()
{
    // TODO: Get view of entities with input component, then set command
}
