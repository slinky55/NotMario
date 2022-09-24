#pragma once

#include <memory>

#include <SFML/Graphics.hpp>
#include <entt/entity/registry.hpp>

// Managers
#include "Managers/RenderManager.h"
#include "Managers/EntityManager.h"

#include "Components/RenderableC.h"

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

    // TODO: Instantiate managers here
    std::shared_ptr<RenderManager> m_renderer = std::make_shared<RenderManager>(m_reg,
                                                                                m_window);
    std::shared_ptr<EntityManager> m_entityMgr = std::make_shared<EntityManager>(m_reg);

    // Entities
    entt::entity m_player;
};
