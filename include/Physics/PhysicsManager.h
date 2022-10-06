#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <forward_list>

#include "entt/entity/registry.hpp"

#include "Entities/Player.h"
#include "PhysicsBody.h"
#include "Constants.h"
#include "Utils/PoolAllocator.h"

namespace p2d
{
    class PhysicsManager
    {
    public:
        explicit PhysicsManager(std::shared_ptr<Player> _player);
        ~PhysicsManager();

        PhysicsBody* Create();
        void Update(float _dt);
    private:
        PoolAllocator m_allocator { 50 };
        std::forward_list<PhysicsBody*> m_bodyList;
        std::shared_ptr<Player> m_player;

        std::size_t m_bodyCount {0};

        static void CheckCollision(PhysicsBody& A,
                                   PhysicsBody& B);
        static void ResolveCollision(Manifold* _manifold);
    };
}