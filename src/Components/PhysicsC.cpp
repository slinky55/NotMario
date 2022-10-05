#include "Physics/PhysicsBody.h"

void PhysicsBody::SetMass(float _mass)
{
    invMass = 1 / _mass;
    mass = _mass;
}

void PhysicsBody::ApplyForce(sf::Vector2f _dir,
                             float _forceInN)
{
    acceleration += (_dir * (_forceInN * invMass));
}

void PhysicsBody::ApplyImpulse(sf::Vector2f _dir,
                               float _force)
{
    velocity += (_dir * (_force * invMass));
}

void PhysicsBody::ClearForces()
{
    acceleration = {0, 0};
}
