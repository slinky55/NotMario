#pragma once

#include <iostream>
#include <cmath>
#include <vector>

#include "entt/entity/registry.hpp"

#include "Entities/Player.h"
#include "PhysicsBody.h"
#include "Constants.h"
#include "Utils/BodyAllocator.h"

namespace p2d
{
    class PhysicsManager
    {
    public:
        PhysicsManager(entt::registry &_reg,
                       std::shared_ptr<Player> _player);

        PhysicsBody* Create();
        void Update(float _dt);
    private:
        entt::registry& m_reg;
        std::shared_ptr<Player> m_player;

        BodyAllocator m_bodyList {50};

        static void CheckCollision(PhysicsBody& A,
                                   PhysicsBody& B);
        static void ResolveCollision(Manifold* _manifold);
    };
}