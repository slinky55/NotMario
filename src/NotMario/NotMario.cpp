
#include "NotMario/NotMario.h"

void NotMario::OnInit()
{
    // Load resources and check for errors
    if (!m_resources->LoadTexture("world_tiles",
                                  "../res/img/world.png"))
    {
        std::cout << "Failed to load world tiles\n";
        m_running = false; return;
    }
    if (!m_resources->LoadTexture("characters",
                                  "../res/img/characters.png"))
    {
        std::cout << "Failed to load player textures\n";
        m_running = false; return;
    }

    // Create window and check for errors
    m_window.create( sf::VideoMode({800, 600}), "NotMario" );
    if (!m_window.isOpen())
    {
        std::cout << "Failed to create window\n";
        m_running = false; return;
    }

    // Initialize player components
    m_player->m_ID = m_entityMgr->Create();
    m_player->m_physComponent = &m_entityMgr->AddPhysicsComponent(m_player->m_ID);
    m_player->m_spriteComponent = &m_entityMgr->AddSpriteComponent(m_player->m_ID);

    m_player->m_physComponent->pos = {400, 300};
    m_player->m_physComponent->collider.halfSize = {16, 16};
    m_player->m_physComponent->collider.centerOffset = {16, 16};
    m_player->m_physComponent->collider.center =
            m_player->m_physComponent->pos + m_player->m_physComponent->collider.centerOffset;

    m_player->m_spriteComponent->sprite.setTexture(m_resources->GetTexture("characters"));
    m_player->m_spriteComponent->sprite.setTextureRect({
       {0, 2 * 32},
       {32, 32}
    });

    m_running = true;
}

void NotMario::Run()
{
    while (m_running)
    {
        if (InputManager::WindowDidClose(m_window))
            m_running = false;
        m_inputMgr->PollInput();

        m_physMgr->Update(time.restart().asSeconds());

        // Game specific updates
        Update();

        m_renderer->Draw();
    }
}

void NotMario::Update()
{
    m_player->m_spriteComponent->sprite.setPosition(m_player->m_physComponent->pos);
}