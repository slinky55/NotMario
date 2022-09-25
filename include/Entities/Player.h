#pragma once

#include <entt/entity/registry.hpp>

#include "Components/Components.h"

struct Player
{
    // ID
    entt::entity m_ID;

    // Components
    PhysicsC* m_physComponent;
    SpriteC* m_spriteComponent;
};