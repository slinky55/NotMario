#include "Physics/PhysicsBody.h"

namespace p2d
{

    void PhysicsBody::SetMass(float _mass)
    {
        invMass = 1 / _mass;
        mass = _mass;
    }

    void PhysicsBody::ApplyForce(Vector2 _dir,
                                 float _forceInN)
    {
        acceleration += (_dir * (_forceInN * invMass));
    }

    void PhysicsBody::ApplyImpulse(Vector2 _dir,
                                   float _force)
    {
        velocity += (_dir * (_force * invMass));
    }

    void PhysicsBody::ClearForces()
    {
        acceleration = {0, 0};
    }

}