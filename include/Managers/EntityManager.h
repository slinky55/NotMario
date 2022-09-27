#pragma once

#include <entt/entity/registry.hpp>

#include "Components/Components.h"

class EntityManager
{
public:
    explicit EntityManager(entt::registry& _reg);

    entt::entity Create();

    // Adding components
    RectangleC& AddRectangleComponent(entt::entity& _ent);
    SpriteC& AddSpriteComponent(entt::entity& _ent);
    PhysicsBody& AddPhysicsComponent(entt::entity& _ent);
    InputC& AddInputComponent(entt::entity& _ent);

private:
    entt::registry& m_reg;
};
