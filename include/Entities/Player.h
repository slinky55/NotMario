#pragma once

#include "entt/entity/entity.hpp"

#include "Components/Components.h"
#include "Physics/PhysicsBody.h"

struct Player
{
    entt::entity ID;

    // Components
    SpriteC* m_spriteComponent;
    p2d::PhysicsBody* m_physComponent;
    InputC* m_inputComponent;
    RectangleC* m_rectComponent;
};