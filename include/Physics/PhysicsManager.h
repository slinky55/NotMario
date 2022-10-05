#pragma once

#include <iostream>
#include <cmath>

#include "entt/entity/registry.hpp"

#include "Entities/Player.h"
#include "PhysicsBody.h"
#include "Constants.h"

namespace p2d
{
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
}