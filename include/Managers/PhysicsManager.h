#pragma once

#include <iostream>
#include <cmath>

#include <entt/entity/registry.hpp>

#include "Components/PhysicsC.h"

constexpr sf::Vector2f UP_NORM {0, -1};

class PhysicsManager
{
public:
    explicit PhysicsManager(entt::registry &_reg,
                            entt::entity& _player);

    void Update(float _dt);
private:
    entt::registry& m_reg;
    entt::entity& m_player;

    sf::Vector2f m_gravity {0.f, 15.f};

    [[nodiscard]] bool AABBDoesCollide(const PhysicsObject& A,
                                       const PhysicsObject& B);
    static void ResolveCollision(PhysicsObject& _player,
                          PhysicsObject& _entity);
};