#include "NotMario/NotMario.h"

void NotMario::OnInit()
{
    m_renderer->OnInit();
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