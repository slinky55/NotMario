#pragma once

#include <iostream>
#include <cmath>

#include <entt/entity/registry.hpp>

#include "Components/PhysicsC.h"
#include "Entities/Player.h"

constexpr sf::Vector2f UP_NORM {0, -1};

class PhysicsManager
{
public:
    explicit PhysicsManager(entt::registry &_reg,
                            Player& _player);

    void Update(float _dt);
private:
    entt::registry& m_reg;
    Player& m_player;

    sf::Vector2f m_gravity {0.f, 15.f};

    [[nodiscard]] bool AABBDoesCollide(const PhysicsC& A,
                                       const PhysicsC& B);
    static void ResolveCollision(PhysicsC& _player,
                                 PhysicsC& _entity);
};