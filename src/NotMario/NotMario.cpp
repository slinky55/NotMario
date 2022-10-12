#include "NotMario/NotMario.h"

//#define SHOW_HITBOX

void NotMario::OnInit()
{
    LoadResources();

    CreateWindow();

    //LoadTestMap();

    LoadMap();

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
        m_animMgr->Update();
        LateUpdate();   // Game related updates
        m_renderer->Draw();
    }
}

void NotMario::Update()
{
    if (m_player->m_inputComponent->cmd == Command::LEFT)
    {
        m_player->m_physComponent->ApplyForce({-1.f, 0.f},
                                              2500.f);
        m_player->m_animComponent->currentAnimation = m_player->m_animComponent->animations["run"];
        m_player->m_animComponent->currentAnimation->play = true;
        m_player->m_spriteComponent->sprite.setTexture(m_player->m_animComponent->currentAnimation->texture);
    }

    if (m_player->m_inputComponent->cmd == Command::RIGHT)
    {
        m_player->m_physComponent->ApplyForce({1.f, 0.f},
                                              2500.f);
        m_player->m_animComponent->currentAnimation = m_player->m_animComponent->animations["run"];
        m_player->m_animComponent->currentAnimation->play = true;
        m_player->m_spriteComponent->sprite.setTexture(m_player->m_animComponent->currentAnimation->texture);
    }

    if (m_player->m_inputComponent->cmd == Command::STOP)
    {
        m_player->m_animComponent->currentAnimation = m_player->m_animComponent->animations["idle"];
        m_player->m_spriteComponent->sprite.setTexture(m_player->m_animComponent->currentAnimation->texture);
    }

    if (m_player->m_inputComponent->cmd == Command::JUMP &&
        m_player->m_physComponent->onGround)
    {
        m_player->m_physComponent->ApplyImpulse(UP_NORM, 375.f);
        m_player->m_physComponent->onGround = false;
    }
}

void NotMario::LateUpdate()
{
    m_player->m_spriteComponent->sprite.setTextureRect(m_player->m_animComponent->currentAnimation->frames[
                                                               m_player->m_animComponent->currentAnimation->currentFrame]);
    m_player->m_spriteComponent->sprite.setPosition({((m_player->m_physComponent->position -
                                                       m_player->m_physComponent->halfSize) * PIXELS_PER_METER).x,
                                                     ((m_player->m_physComponent->position -
                                                       m_player->m_physComponent->halfSize) * PIXELS_PER_METER).y});
#ifdef SHOW_HITBOX
    m_player->m_rectComponent->rect.setPosition({((m_player->m_physComponent->position -
                                                   m_player->m_physComponent->halfSize) * PIXELS_PER_METER).x,
                                                 ((m_player->m_physComponent->position -
                                                   m_player->m_physComponent->halfSize) * PIXELS_PER_METER).y});
#endif
}

void NotMario::CreatePlayer()
{
    m_player->ID = m_entityMgr->Register();

    // src
    m_player->m_physComponent = m_physMgr->Create();
    assert(m_player->m_physComponent);
    m_player->m_physComponent->position = { 200 / PIXELS_PER_METER, 200 / PIXELS_PER_METER};
    m_player->m_physComponent->halfSize = {( (18 * 1.5f) / 2.f) / PIXELS_PER_METER, ( (23 * 1.5f) / 2.f) / PIXELS_PER_METER};
    m_player->m_physComponent->collider = {
            m_player->m_physComponent->position,
            m_player->m_physComponent->halfSize
    };
    m_player->m_physComponent->SetMass(70.f);
    m_player->m_physComponent->type = p2d::PhysicsType::DYNAMIC;
    m_player->m_physComponent->hasGravity = true;

#ifdef SHOW_HITBOX
    m_player->m_rectComponent = &m_entityMgr->AddRectangleComponent(m_player->ID);
    m_player->m_rectComponent->rect.setOutlineThickness(1);
    m_player->m_rectComponent->rect.setOutlineColor(sf::Color::White);
    m_player->m_rectComponent->rect.setFillColor(sf::Color::Transparent);
    m_player->m_rectComponent->rect.setSize( {18, 23} );
    m_player->m_rectComponent->rect.setPosition({((m_player->m_physComponent->position -
                                                   m_player->m_physComponent->halfSize) * PIXELS_PER_METER).x,
                                                 ((m_player->m_physComponent->position -
                                                   m_player->m_physComponent->halfSize) * PIXELS_PER_METER).y});
    m_player->m_rectComponent->rect.setScale({1.5, 1.5});
#endif
    // Input
    m_player->m_inputComponent = &m_entityMgr->AddInputComponent(m_player->ID);

    m_player->m_animComponent = &m_entityMgr->AddAnimationComponent(m_player->ID);
    m_player->m_animComponent->animations.emplace("run", new Animation {
        m_resources->GetTexture("characters")
    });
    m_player->m_animComponent->animations.emplace("idle", new Animation {
        m_resources->GetTexture("characters")
    });

    Animation* run = m_player->m_animComponent->animations["run"];
    run->frames.push_back({ {326, 73}, {18, 23} });
    run->frames.push_back({ {358, 73}, {18, 23} });
    run->frames.push_back({ {390, 73}, {18, 23} });
    run->totalFrames = 3;
    run->frameTime = 16;

    Animation* idle = m_player->m_animComponent->animations["idle"];
    idle->frames.push_back({ {6, 73}, {18, 23} });
    idle->totalFrames = 1;
    idle->frameTime = 0;
    m_player->m_animComponent->currentAnimation = idle;

    m_player->m_spriteComponent = &m_entityMgr->AddSpriteComponent(m_player->ID);
    m_player->m_spriteComponent->sprite.setTexture(m_player->m_animComponent->currentAnimation->texture);
    m_player->m_spriteComponent->sprite.setPosition({((m_player->m_physComponent->position -
                                                       m_player->m_physComponent->halfSize) * PIXELS_PER_METER).x,
                                                     ((m_player->m_physComponent->position -
                                                       m_player->m_physComponent->halfSize) * PIXELS_PER_METER).y});
    m_player->m_spriteComponent->sprite.setScale({1.5, 1.5});
}

void NotMario::CreateWindow()
{
    m_window.create( sf::VideoMode({800, 600}), "NotMario" );
    if (!m_window.isOpen())
    {
        std::cout << "Failed to create window\n";
        m_running = false; return;
    }
    m_window.setFramerateLimit(60);
}

void NotMario::LoadResources()
{
    if (!m_resources->LoadTexture("tileset",
                                  "../../../res/img/tilesheet.png"))
    {
        std::cout << "Failed to load world tiles\n";
        m_running = false; return;
    }
    if (!m_resources->LoadTexture("characters",
                                  "../../../res/img/characters.png"))
    {
        std::cout << "Failed to load player textures\n";
        m_running = false; return;
    }
}

void NotMario::LoadTestMap()
{
    sf::Color blockColor = sf::Color::Green;

    // Floor
    CreateMapBlock({400, (600 - 16)},
                   {800, 32},
                   blockColor);
    // Ceiling
    CreateMapBlock({400, 16},
                   {800, 32},
                   blockColor);

    // Left
    CreateMapBlock({16, 300},
                   {32, 568},
                   blockColor);

    // Right
    CreateMapBlock({(800 - 16), 300},
                   {32, 568},
                   blockColor);

    // Steps
    CreateMapBlock({400, (600 - 48)},
                   {32, 32},
                   blockColor);

    CreateMapBlock({432, (600 - 48)},
                   {32, 32},
                   blockColor);

    CreateMapBlock({432, (600 - 80)},
                   {32, 32},
                   blockColor);

    CreateMapBlock({464, (600 - 48)},
                   {32, 32},
                   blockColor);
}

void NotMario::LoadMap()
{

    std::fstream in {"../../../res/maps/TestScene_1/TestScene_1.map"};
    if (!in.is_open())
        std::cout << "Failed to open map file\n";

    std::vector<std::vector<int>> layer;
    std::string line, num;

    while (std::getline(in, line))
    {
        auto& row = layer.emplace_back();
        std::stringstream ss {line};
        while (std::getline(ss, num, ','))
        {
            row.push_back(std::stoi(num));
        }
    }

    in.close();

    m_tileset.emplace(COIN_BLOCK_ACTIVE, new TileProperties {
        m_resources->GetTexture("tileset"),
        { {2 * 32, 7 * 32 }, {32, 32} },
        {32, 32},
        true
    });

    m_tileset.emplace(BRICK, new TileProperties {
        m_resources->GetTexture("tileset"),
        { {1 * 32, 6 * 32 }, {32, 32} },
        {32, 32},
        true
    });

    m_tileset.emplace(PIPE_UP, new TileProperties {
            m_resources->GetTexture("tileset"),
            { {3 * 32, 8 * 32 }, {64, 64} },
            {64, 64},
            true
    });

    m_tileset.emplace(FLOOR, new TileProperties {
            m_resources->GetTexture("tileset"),
            { {0 * 32, 6 * 32 }, {32, 32} },
            {32, 32},
            true
    });

    for (uint32_t row = 0; row < layer.size(); row++)
    {
        for (uint32_t col = 0; col < layer[row].size(); col++)
        {
            if (layer[row][col] == -1) continue;
            auto type = static_cast<TileType>(layer[row][col]);
            auto tile = m_entityMgr->Register();
            auto* phys = m_physMgr->Create();

            phys->halfSize = {
                    (m_tileset[type]->size.x / 2.f) / PIXELS_PER_METER,
                    (m_tileset[type]->size.y / 2.f) / PIXELS_PER_METER,
            };

            phys->position = {
                    ((col * GRID_SIZE) / PIXELS_PER_METER) + phys->halfSize.x,
                    ((row * GRID_SIZE) / PIXELS_PER_METER) + phys->halfSize.y
            };

            phys->collider = {
                    phys->position,
                    phys->halfSize
            };
            phys->type = p2d::PhysicsType::STATIC;

            auto& sprite = m_entityMgr->AddSpriteComponent(tile);
            sprite.sprite.setTexture(m_tileset[type]->tex);
            sprite.sprite.setTextureRect(m_tileset[type]->rect);
            sprite.sprite.setPosition({col * 32.f, row * 32.f});
        }
    }
}

void NotMario::CreateMapBlock(const sf::Vector2f& _pos,
                              const sf::Vector2f& _size,
                              const sf::Color& _color)
{
    auto& block = m_mapBlocks.emplace_back();
    block = std::make_shared<Block>();
    block->ID = m_entityMgr->Register();

    block->m_physicsComponent = m_physMgr->Create();
    assert(block->m_physicsComponent);

    block->m_physicsComponent->position = {
            _pos.x / PIXELS_PER_METER,
            _pos.y / PIXELS_PER_METER
    };
    block->m_physicsComponent->halfSize = {
            (_size.x / 2.f) / PIXELS_PER_METER,
            (_size.y / 2.f) / PIXELS_PER_METER
    };
    block->m_physicsComponent->collider = {
            block->m_physicsComponent->position,
            block->m_physicsComponent->halfSize
    };

    block->m_rectComponent = &m_entityMgr->AddRectangleComponent(block->ID);
    block->m_rectComponent->rect.setPosition( {(block->m_physicsComponent->position.x - block->m_physicsComponent->halfSize.x) * PIXELS_PER_METER,
                                               (block->m_physicsComponent->position.y - block->m_physicsComponent->halfSize.y) * PIXELS_PER_METER} );
    block->m_rectComponent->rect.setSize(_size);
#ifdef  SHOW_COLLIDERS
    block->m_rectComponent->rect.setFillColor(sf::Color::Black);
    block->m_rectComponent->rect.setOutlineColor(_color);
    block->m_rectComponent->rect.setOutlineThickness(1.f);
#else
    block->m_rectComponent->rect.setFillColor(_color);
#endif
}
