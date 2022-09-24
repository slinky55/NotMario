#include "NotMario/NotMario.h"

void NotMario::OnInit()
{
    m_renderer->OnInit();

    // Create entities for game
    m_player = m_entityMgr->Create();

    auto& playerR = m_reg.emplace<RenderableC>(m_player);
    playerR.drawable = std::make_shared<sf::RectangleShape>();

    auto drawable = std::reinterpret_pointer_cast<sf::RectangleShape>(playerR.drawable);
    drawable->setPosition({400, 300});
    drawable->setSize({100, 100});
    drawable->setFillColor(sf::Color::White);
}

void NotMario::Run()
{
    while (m_window.isOpen())
    {
        sf::Event e{};
        while (m_window.pollEvent(e))
            if (e.type == sf::Event::Closed)
                m_window.close();

        m_renderer->Draw();
    }
}