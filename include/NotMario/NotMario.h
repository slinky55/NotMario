#pragma once

#include <memory>

#include "entt/entity/registry.hpp"

#include "Managers/RenderManager.h"

class NotMario
{
public:
    NotMario() = default;
    ~NotMario() = default;

    void OnInit();
private:
    entt::registry m_reg;
    sf::RenderWindow m_window;

    // TODO: Instantiate managers here
    std::shared_ptr<RenderManager> m_renderer =
            std::make_shared<RenderManager>(m_reg,
                                            m_window);

    // Entities
    entt::entity m_player;
};
