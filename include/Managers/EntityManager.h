#pragma once

#include <entt/entity/registry.hpp>

#include "Components/RenderableC.h"
#include "Components/PhysicsC.h"

class EntityManager
{
public:
    explicit EntityManager(entt::registry& _reg);

    entt::entity Create();

    // Adding components
    RenderableC& AddSprite(entt::entity _ent);
    PhysicsC& AddPhysics(entt::entity _ent);
private:
    entt::registry& m_reg;
};
