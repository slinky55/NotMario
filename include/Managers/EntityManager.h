#pragma once

#include <entt/entity/registry.hpp>

#include "Components/SpriteC.h"
#include "Components/PhysicsC.h"
#include "Components/RectangleC.h"

class EntityManager
{
public:
    explicit EntityManager(entt::registry& _reg);

    entt::entity Create();

    // Adding components
    RectangleC& AddRectangleComponent(entt::entity& _ent);
    SpriteC& AddSpriteComponent(entt::entity& _ent);
    PhysicsC& AddPhysicsComponent(entt::entity& _ent);

private:
    entt::registry& m_reg;
};
