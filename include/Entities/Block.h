#pragma once

#include <entt/entity/entity.hpp>

#include "Components/RectangleC.h"
#include "Physics/PhysicsBody.h"

struct Block
{
    entt::entity ID;

    // Components
    RectangleC* m_rectComponent;
    p2d::PhysicsBody* m_physicsComponent;
};