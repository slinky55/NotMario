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
#include "Managers/AnimationManager.h"

// Components
#include "Components/Components.h"

// Entities
#include "Entities/Player.h"

#include "Map.h"

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
    std::unique_ptr<ResourceManager> m_resources = std::make_unique<ResourceManager>();
    std::unique_ptr<RenderManager> m_renderer = std::make_unique<RenderManager>(m_reg,
                                                                                m_window);
    std::unique_ptr<EntityManager> m_entityMgr = std::make_unique<EntityManager>(m_reg);
    std::unique_ptr<p2d::PhysicsManager> m_physMgr = std::make_unique<p2d::PhysicsManager>(m_player);
    std::unique_ptr<InputManager> m_inputMgr = std::make_unique<InputManager>(m_reg);
    std::unique_ptr<AnimationManager> m_animMgr = std::make_unique<AnimationManager>(m_reg);

    void Update();
    void LateUpdate();

    void CreatePlayer();
    void CreateMapBlock(const sf::Vector2f& _pos,
                        const sf::Vector2f& _size,
                        const sf::Color& _color);

    TileSet m_tileset;

    void CreateWindow();
    void LoadResources();
    void LoadMap();
    void LoadTestMap();
};
