#pragma once

#include <iostream>
#include <cmath>

#include <entt/entity/registry.hpp>

#include "Components/PhysicsC.h"
#include "Entities/Player.h"

constexpr sf::Vector2f UP_NORM {0, -1};
constexpr sf::Vector2f DOWN_NORM {0, 1};

class PhysicsManager
{
public:
    PhysicsManager(entt::registry &_reg,
                   Player& _player);

    void Update(float _dt);

    static void SetMass(PhysicsBody& _body, float _mass);
    static void ClearForces(PhysicsBody& _body);
    static void ApplyForce(PhysicsBody& _body,
                           sf::Vector2f _dir,
                           float _forceInN);
private:
    entt::registry& m_reg;
    Player& m_player;

    sf::Vector2f m_gravity {0.f, 9.8f};

    static void CheckCollision(PhysicsBody& A,
                                PhysicsBody& B);
    static void ResolveCollision(Manifold* _manifold);
};