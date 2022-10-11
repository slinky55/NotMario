#pragma once

// std
#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include <sstream>

// 3rd party
#include <SFML/Graphics.hpp>
#include <entt/entity/registry.hpp>

// Managers
#include "Managers/RenderManager.h"
#include "Managers/EntityManager.h"
#include "Managers/ResourceManager.h"
#include "Physics/PhysicsManager.h"
#include "Managers/InputManager.h"

// Components
#include "Components/Components.h"

// Entities
#include "Entities/Player.h"

#include "Map.h"

constexpr float MAP_WIDTH = 50.f;
constexpr float MAP_HEIGHT = 38.f;

constexpr float GRID_SIZE = 32.f;

class NotMario
{
public:
    NotMario() = default;
    ~NotMario() = default;

    void OnInit();
    void Run();
    void OnClose();
private:
    bool m_running = false;

    entt::registry m_reg;
    std::shared_ptr<Map> m_map = std::make_shared<Map>();

    sf::RenderWindow m_window;
    sf::Clock time;

    // Entities
    std::shared_ptr<Player> m_player = std::make_shared<Player>();
    std::vector<std::shared_ptr<Block>> m_mapBlocks;

    // TODO: Instantiate managers here
    std::shared_ptr<ResourceManager> m_resources = std::make_shared<ResourceManager>();
    std::shared_ptr<RenderManager> m_renderer = std::make_shared<RenderManager>(m_reg,
                                                                                m_window);
    std::shared_ptr<EntityManager> m_entityMgr = std::make_shared<EntityManager>(m_reg);
    std::shared_ptr<p2d::PhysicsManager> m_physMgr = std::make_shared<p2d::PhysicsManager>(m_player);
    std::shared_ptr<InputManager> m_inputMgr = std::make_shared<InputManager>(m_reg);

    void Update();
    void LateUpdate();

    void CreatePlayer();
    void CreateMapBlock(const sf::Vector2f& _pos,
                        const sf::Vector2f& _size,
                        const sf::Color& _color);

    TileSet m_tileset;

    void LoadMap();
    void LoadTestMap();
};
