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
    Command cmd = Command::STOP;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        cmd = Command::LEFT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        cmd = Command::RIGHT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        cmd = Command::JUMP;

    auto view = m_reg.view<InputC>();

    for (auto& ent : view)
    {
        auto& inputC = view.get<InputC>(ent);
        inputC.cmd = cmd;
    }
}
