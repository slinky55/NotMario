
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

    m_map->numLayers = 2;

    ParseMapData("sampleMap", *m_map);

    // Load tileset data
    m_map->tileset[TileType::ROCK_GROUND_LEFT] = new TileProperties {
        m_resources->GetTexture("world_tiles"),
        {{10 * 16, 0 * 16}, {16, 16}},
        {16, 16}
    };

    m_map->tileset[TileType::ROCK_GROUND_MIDDLE] = new TileProperties {
        m_resources->GetTexture("world_tiles"),
        {{11 * 16, 0 * 16}, {16, 16}},
        {16, 16}
    };

    m_map->tileset[TileType::ROCK_GROUND_RIGHT] = new TileProperties {
        m_resources->GetTexture("world_tiles"),
        {{12 * 16, 0 * 16}, {16, 16}},
        {16, 16}
    };

    m_map->tileset[TileType::ROCK_WALL_LEFT] = new TileProperties {
        m_resources->GetTexture("world_tiles"),
        {{10 * 16, 1 * 16}, {16, 16}},
        {16, 16}
    };

    m_map->tileset[TileType::DIRT_MIDDLE] = new TileProperties {
        m_resources->GetTexture("world_tiles"),
        {{11 * 16, 1 * 16}, {16, 16}},
        {16, 16}
    };

    m_map->tileset[TileType::ROCK_WALL_RIGHT] = new TileProperties {
        m_resources->GetTexture("world_tiles"),
        {{12 * 16, 1 * 16}, {16, 16}},
        {16, 16}
    };

    m_map->tileset[TileType::BACKGROUND] = new TileProperties {
        m_resources->GetTexture("background"),
        {{0, 0}, {16, 16}},
        {16, 16}
    };

    // Initialize player components
    m_player->m_ID = m_entityMgr->Create();

    m_player->m_physComponent = &m_entityMgr->AddPhysicsComponent(m_player->m_ID);
    m_player->m_spriteComponent = &m_entityMgr->AddSpriteComponent(m_player->m_ID);
    m_player->m_inputComponent = &m_entityMgr->AddInputComponent(m_player->m_ID);

    m_player->m_physComponent->pos = {400, 300};
    m_player->m_physComponent->collider.halfSize = {16, 16};
    m_player->m_physComponent->collider.centerOffset = {16, 16};
    m_player->m_physComponent->collider.center =
            m_player->m_physComponent->pos + m_player->m_physComponent->collider.centerOffset;
    m_player->m_physComponent->mass = 25.f;

//    m_player->m_spriteComponent->sprite.setTexture(m_resources->GetTexture("characters"));
//    m_player->m_spriteComponent->sprite.setTextureRect({
//       {0, 2 * 32},
//       {32, 32}
//    });

    m_player->m_rectComponent = &m_entityMgr->AddRectangleComponent(m_player->m_ID);
    m_player->m_rectComponent->rect.setSize({32, 32});
    m_player->m_rectComponent->rect.setPosition(m_player->m_physComponent->pos);
    m_player->m_rectComponent->rect.setFillColor(sf::Color::White);

    LoadMap();

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
        m_player->m_physComponent->vel.x = -50;
    if (m_player->m_inputComponent->cmd == Command::RIGHT)
        m_player->m_physComponent->vel.x = 50;
    if (m_player->m_inputComponent->cmd == Command::JUMP)
    {
        if (m_player->m_physComponent->onGround)
            m_player->m_physComponent->didJump = true;
    }
    if (m_player->m_inputComponent->cmd == Command::STOP)
        m_player->m_physComponent->vel.x = 0;
}

void NotMario::LateUpdate()
{
//    m_player->m_spriteComponent->sprite.setPosition(m_player->m_physComponent->pos);
    m_player->m_rectComponent->rect.setPosition(m_player->m_physComponent->pos);
}

void NotMario::LoadMap()
{
    sf::Vector2f position;
    TileType type;

    for (int layer = 0; layer < m_map->numLayers; layer++)
    {
        MapLayer& current = m_map->layers[layer];
        for (int row = 0; row < MAP_HEIGHT; row++)
        {
            for (int col = 0; col < MAP_WIDTH; col++)
            {
                type = static_cast<TileType>(current[row][col]);

                if (type == TileType::TRANSPARENT) continue;

                auto tile = m_entityMgr->Create();

                position = {
                        m_map->tileset[type]->size.x * col,
                        m_map->tileset[type]->size.y * row,
                };

                auto& spriteC = m_entityMgr->AddSpriteComponent(tile);
                spriteC.sprite.setTexture(m_map->tileset[type]->tex);
                spriteC.sprite.setTextureRect(m_map->tileset[type]->rect);
                spriteC.sprite.setPosition(position);

                if (type != TileType::BACKGROUND)
                {
                    auto& physC = m_entityMgr->AddPhysicsComponent(tile);
                    physC.pos = {
                        m_map->tileset[type]->size.x * col,
                        m_map->tileset[type]->size.y * row,
                    };
                    physC.size = {16, 16};
                    physC.type = PhysicsType::STATIC;
                    physC.collider.halfSize = {8, 8};
                    physC.collider.centerOffset = {8, 8};
                    physC.collider.center = physC.pos + physC.collider.centerOffset;
                }
            }
        }
    }
}
