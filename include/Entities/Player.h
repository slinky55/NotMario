#pragma once

#include <entt/entity/registry.hpp>

#include "Components/Components.h"

struct Player
{
    // ID
    entt::entity m_ID {0};

    // Components
    PhysicsBody* m_physComponent {nullptr};
    SpriteC* m_spriteComponent {nullptr};
    InputC* m_inputComponent {nullptr};
    RectangleC* m_rectComponent {nullptr};
};