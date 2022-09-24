
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
    auto& playerP = m_reg.emplace<PhysicsObject>(m_player);

    playerR.sprite = std::make_shared<sf::Sprite>();
    playerR.sprite->setTexture(m_resources->GetTexture("characters"));
    playerR.sprite->setTextureRect({ {1 * 32, 0 * 32}, {32, 32} });
    playerR.sprite->setPosition({400, 300});
    playerR.sprite->setScale({2, 2});

    playerP.pos = {400, 300};
    playerP.size = {64, 64};
    playerP.collider.halfSize = {32, 32};
    playerP.collider.centerOffset = {32, 32};
    playerP.collider.center = {playerP.pos + playerP.collider.centerOffset};
    playerP.isDynamic = true;

    for (int i = 0; i < 50; i++)
    {
        auto tile = m_entityMgr->Create();

        auto& tileR = m_entityMgr->AddSprite(tile);
        tileR.sprite = std::make_shared<sf::Sprite>();
        tileR.sprite->setTexture(m_resources->GetTexture("world_tiles"));
        tileR.sprite->setTextureRect({
                                             {8 * 16, 0 * 16},
                                             {16, 16}
                                     });
        tileR.sprite->setScale({2, 2});
        tileR.sprite->setPosition({i * 32.f,
                                   600 - 32});

        auto& tileP = m_reg.emplace<PhysicsObject>(tile);
        tileP.pos = {tileR.sprite->getPosition()};
        tileP.size = {32, 32};
        tileP.collider.halfSize = {16, 16};
        tileP.collider.centerOffset = tileP.collider.halfSize;
        tileP.collider.center = {tileP.pos + tileP.collider.centerOffset};
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

        auto& playerP = m_reg.get<PhysicsObject>(m_player);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            playerP.vel.x = -200;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            playerP.vel.x = 200;
        else
            playerP.vel.x = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !playerP.jump)
            if (playerP.onGround)
                playerP.jump = true;


        Update();
        m_renderer->Draw();
    }
}

void NotMario::Update()
{
    m_physMgr->Update(time.restart().asSeconds());

    auto& playerP = m_reg.get<PhysicsObject>(m_player);
    auto& playerR = m_reg.get<RenderableC>(m_player);

    playerR.sprite->setPosition(playerP.pos);
}