#pragma once

#include <entt/entity/registry.hpp>

#include "Components/Components.h"

#include "Entities/Player.h"
#include "Entities/Block.h"
#include "Physics/Constants.h"

class EntityManager
{
public:
    explicit EntityManager(entt::registry& _reg);

    entt::entity Register();

    // Prefabs
    entt::entity CreateBlock(const sf::Vector2f& _pos,
                             const sf::Vector2f& _size,
                             const sf::Color& _color);

    // Adding components
    RectangleC& AddRectangleComponent(entt::entity& _ent);
    SpriteC& AddSpriteComponent(entt::entity& _ent);
    p2d::PhysicsBody& AddPhysicsComponent(entt::entity& _ent);
    InputC& AddInputComponent(entt::entity& _ent);
    AnimationC& AddAnimationComponent(entt::entity& _ent);

private:
    entt::registry& m_reg;
};
