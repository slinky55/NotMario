#pragma once

#include "Components/RectangleC.h"
#include "Components/PhysicsC.h"

#include "Entities/Entity.h"

struct Block : public Entity
{
    // Components
    RectangleC* m_rectComponent;
    PhysicsBody* m_physicsComponent;
};