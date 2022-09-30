#pragma once

#include <iostream>
#include <cmath>

#include <entt/entity/registry.hpp>

#include "Components/PhysicsC.h"
#include "Prefabs/Player.h"
#include "Constants.h"

class PhysicsManager
{
public:
    PhysicsManager(entt::registry &_reg,
                   std::shared_ptr<Player> _player);

    void Update(float _dt);
private:
    entt::registry& m_reg;
    std::shared_ptr<Player> m_player;

    static void CheckCollision(PhysicsBody& A,
                                PhysicsBody& B);
    static void ResolveCollision(Manifold* _manifold);
};