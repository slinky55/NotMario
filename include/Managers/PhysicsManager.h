#pragma once

#include <iostream>
#include <cmath>

#include <entt/entity/registry.hpp>

#include "Components/PhysicsC.h"

class PhysicsManager
{
public:
    explicit PhysicsManager(entt::registry &_reg,
                            entt::entity& _player);

    void Update(float _dt);
private:
    entt::registry& m_reg;
    entt::entity& m_player;

    sf::Vector2f m_gravity {0.f, 9.8f};

    [[nodiscard]] bool AABBDoesCollide(const AABB& A,
                         const AABB& B);
};