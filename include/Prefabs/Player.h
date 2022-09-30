#pragma once

#include <optional>

#include "entt/entity/registry.hpp"

#include "Components/Components.h"
#include "Entities/Entity.h"

struct Player
{
    entt::entity ID;

    // Components
    SpriteC* m_spriteComponent;
    PhysicsBody* m_physComponent;
    InputC* m_inputComponent;
    RectangleC* m_rectComponent;
};