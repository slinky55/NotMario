
#include "NotMario/NotMario.h"

void NotMario::OnInit()
{
    // Load resources
    if (!m_resources->LoadTexture("world_tiles",
                                  "../res/img/world.png"))
        std::cout << "Failed to load world tiles\n";
    if (!m_resources->LoadTexture("characters",
                                  "../res/img/characters.png"))
        std::cout << "Failed to load player textures\n";

    m_renderer->OnInit();

    // Load the player
    m_player = m_entityMgr->Create();

    auto& playerR = m_entityMgr->AddSprite(m_player);
    auto& playerPhys = m_entityMgr->AddPhysics(m_player);

    playerR.sprite = std::make_shared<sf::Sprite>();
    playerR.sprite->setTexture(m_resources->GetTexture("characters"));
    playerR.sprite->setTextureRect({ {1 * 32, 0 * 32}, {32, 32} });
    playerR.sprite->setOrigin({16, 16});
    playerR.sprite->setPosition({400, 300});
    playerR.sprite->setScale({2, 2});

    playerPhys.bodyDef.type = b2_dynamicBody;
    playerPhys.bodyDef.position.Set(400 / PHYS_COORD_CONVERSION,
                                    300 / PHYS_COORD_CONVERSION);
    playerPhys.body = m_physMgr->RegisterBody(&playerPhys.bodyDef);
    assert(playerPhys.body);
    playerPhys.box.SetAsBox((64.f / PHYS_COORD_CONVERSION) / 2.f,
                            (64.f / PHYS_COORD_CONVERSION) / 2.f);
    playerPhys.fixture.shape = &playerPhys.box;
    playerPhys.fixture.density = 1.f;
    playerPhys.fixture.friction = 0.3f;
    playerPhys.body->CreateFixture(&playerPhys.fixture);

    for (int i = 0; i < 30; i++)
    {
        auto tile = m_entityMgr->Create();

        auto& tileR = m_entityMgr->AddSprite(tile);
        tileR.sprite = std::make_shared<sf::Sprite>();
        tileR.sprite->setTexture(m_resources->GetTexture("world_tiles"));
        tileR.sprite->setTextureRect({
            {8 * 16, 0 * 16},
            {16, 16}
        });
        tileR.sprite->setOrigin({8, 8});
        tileR.sprite->setScale({4, 4});
        tileR.sprite->setPosition({i * 64.f, 568});

        auto& tileP = m_entityMgr->AddPhysics(tile);
        tileP.bodyDef.position.Set(i * 64.f / PHYS_COORD_CONVERSION,
                                   568 / PHYS_COORD_CONVERSION);
        tileP.body = m_physMgr->RegisterBody(&tileP.bodyDef);
        assert(tileP.body);
        tileP.box.SetAsBox((64.f / PHYS_COORD_CONVERSION) / 2.f,
                                (64.f / PHYS_COORD_CONVERSION) / 2.f);
        tileP.body->CreateFixture(&tileP.box, 0.f);
    }
}

void NotMario::Run()
{
    while (m_window.isOpen())
    {
        sf::Event e{};
        while (m_window.pollEvent(e))
            if (e.type == sf::Event::Closed)
                m_window.close();

        Update();
        m_renderer->Draw();
    }
}

void NotMario::Update()
{
    m_physMgr->Update(time.restart().asSeconds());

    auto& rendComp = m_reg.get<RenderableC>(m_player);
    auto& physComp = m_reg.get<PhysicsC>(m_player);
    auto renderable = std::reinterpret_pointer_cast<sf::Sprite>(rendComp.sprite);
    renderable->setPosition({physComp.body->GetPosition().x * PHYS_COORD_CONVERSION,
                             physComp.body->GetPosition().y * PHYS_COORD_CONVERSION});
}