#include "NotMario/NotMario.h"

#define DEBUG_DRAW

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
    if (!m_resources->LoadTexture("background",
                                  "../res/img/bg.png"))
    {
        std::cout << "Failed to load background texture\n";
        m_running = false; return;
    }

    // Create window and check for errors
    m_window.create( sf::VideoMode({800, 600}), "NotMario" );
    if (!m_window.isOpen())
    {
        std::cout << "Failed to create window\n";
        m_running = false; return;
    }
    m_window.setFramerateLimit(60);

    LoadTestMap();

    CreatePlayer();

    m_running = true;
}

void NotMario::Run()
{
    while (m_running)
    {
        if (InputManager::WindowDidClose(m_window))
            m_running = false;
        m_inputMgr->PollInput();
        Update();       // Input updates
        m_physMgr->Update(time.restart().asSeconds());
        LateUpdate();   // Game related updates
        m_renderer->Draw();
    }
}

void NotMario::Update()
{
    if (m_player->m_inputComponent->cmd == Command::LEFT)
    {
        m_player->m_physComponent->ApplyForce({-1.f, 0.f},
                                              5000.f);
    }

    if (m_player->m_inputComponent->cmd == Command::RIGHT)
    {
        m_player->m_physComponent->ApplyForce({1.f, 0.f},
                                              5000.f);
    }

    if (m_player->m_inputComponent->cmd == Command::JUMP &&
        m_player->m_physComponent->onGround)
    {
        m_player->m_physComponent->ApplyImpulse(UP_NORM, 350.f);
        m_player->m_physComponent->onGround = false;
    }
}

void NotMario::LateUpdate()
{

#ifdef DEBUG_DRAW
    m_player->m_rectComponent->rect.setPosition( (m_player->m_physComponent->position -
                                                  m_player->m_physComponent->halfSize) * PIXELS_PER_METER);
#else
    m_player->m_spriteComponent->sprite.setPosition((m_player->m_physComponent->position -
                                                     m_player->m_physComponent->halfSize) * PIXELS_PER_METER);
#endif
}

void NotMario::CreatePlayer()
{
    m_player->ID = m_entityMgr->Register();

    m_player->m_rectComponent = &m_entityMgr->AddRectangleComponent(m_player->ID);
    m_player->m_physComponent = &m_entityMgr->AddPhysicsComponent(m_player->ID);
    m_player->m_inputComponent = &m_entityMgr->AddInputComponent(m_player->ID);

    assert(m_player->m_rectComponent &&
           m_player->m_physComponent &&
           m_player->m_inputComponent);

    m_player->m_physComponent->position = { 200 / PIXELS_PER_METER, 200 / PIXELS_PER_METER};
    m_player->m_physComponent->halfSize = {16 / PIXELS_PER_METER, 16 / PIXELS_PER_METER};
    m_player->m_physComponent->collider = {
            m_player->m_physComponent->position,
            m_player->m_physComponent->halfSize
    };
    m_player->m_physComponent->SetMass(70.f);
    m_player->m_physComponent->type = PhysicsType::DYNAMIC;
    m_player->m_physComponent->hasGravity = true;

#ifdef DEBUG_DRAW
    m_player->m_rectComponent->rect.setSize({32, 32});
    m_player->m_rectComponent->rect.setFillColor(sf::Color::White);
    m_player->m_rectComponent->rect.setPosition( (m_player->m_physComponent->position -
                                                  m_player->m_physComponent->halfSize) * PIXELS_PER_METER);
#else
        m_player->m_spriteComponent->sprite.setTexture(m_resources->GetTexture("characters"));
        m_player->m_spriteComponent->sprite.setTextureRect({
           {0, 2 * 32},
           {32, 32}
        });
#endif
}

void NotMario::LoadTestMap()
{
    sf::Color blockColor = sf::Color::Green;

    // Floor
    m_entityMgr->CreateBlock(
            {400, (600 - 16)},
            {800, 32},
            blockColor
    );

    // Ceiling
    m_entityMgr->CreateBlock(
            {400, 16},
            {800, 32},
            blockColor
    );

    // Left wall
    m_entityMgr->CreateBlock(
            {16, 300},
            {32, 568},
            blockColor
    );

    // Right wall
    m_entityMgr->CreateBlock(
            {(800 - 16), 300},
            {32, 568},
            blockColor
    );

    // Steps
    m_entityMgr->CreateBlock(
            {400, (600 - 48)},
            {32, 32},
            blockColor
    );
    m_entityMgr->CreateBlock(
            {432, (600 - 80)},
            {32, 32},
            blockColor
    );

}
