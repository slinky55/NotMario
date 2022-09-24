#pragma once

// std
#include <iostream>
#include <memory>

// 3rd party
#include <SFML/Graphics.hpp>
#include <entt/entity/registry.hpp>

// Managers
#include "Managers/RenderManager.h"
#include "Managers/EntityManager.h"
#include "Managers/ResourceManager.h"
#include "Managers/PhysicsManager.h"

// Components
#include "Components/RenderableC.h"
#include "Components/PhysicsC.h"

class NotMario
{
public:
    NotMario() = default;
    ~NotMario() = default;

    void OnInit();
    void Run();
private:
    entt::registry m_reg;
    sf::RenderWindow m_window;
    sf::Clock time;

    // TODO: Instantiate managers here
    std::shared_ptr<ResourceManager> m_resources = std::make_shared<ResourceManager>();
    std::shared_ptr<RenderManager> m_renderer = std::make_shared<RenderManager>(m_reg,
                                                                                m_window);
    std::shared_ptr<EntityManager> m_entityMgr = std::make_shared<EntityManager>(m_reg);
    std::shared_ptr<PhysicsManager> m_physMgr = std::make_shared<PhysicsManager>(m_reg, m_player);
    // Entities
    entt::entity m_player {0};

    bool jumping = false;

    void Update();
};
