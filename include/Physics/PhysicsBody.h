#pragma once

#include "Math/Vector2.h"
#include "AABB.h"

namespace p2d
{
    enum class PhysicsType
    {
        DYNAMIC,
        STATIC
    };

    struct PhysicsBody
    {
        Vector2 position,
                velocity,
                acceleration;

        Vector2 halfSize;

        AABB collider;

        bool hasGravity {false};
        bool onGround {false};

        float invMass {0};
        float mass {0};

        PhysicsType type {PhysicsType::STATIC};

        void SetMass(float _mass);
        void ApplyForce(Vector2 _dir,
                        float _forceInN);
        void ApplyImpulse(Vector2 _dir,
                          float _force);
        void ClearForces();

    };

    struct Manifold
    {
        PhysicsBody& A;
        PhysicsBody& B;

        Vector2 depth;
    };
}
