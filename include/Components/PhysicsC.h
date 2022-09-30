#pragma once

#include <SFML/System/Vector2.hpp>

enum class PhysicsType
{
    DYNAMIC,
    STATIC
};

struct AABB
{
    sf::Vector2f center;
    sf::Vector2f halfSize;
};

struct PhysicsBody
{
    sf::Vector2f position,
                 velocity,
                 acceleration;

    sf::Vector2f halfSize;

    AABB collider;

    bool hasGravity {false};
    bool onGround {false};

    float invMass {0};
    float mass {0};

    PhysicsType type {PhysicsType::STATIC};

    void SetMass(float _mass);
    void ApplyForce(sf::Vector2f _dir,
                    float _forceInN);
    void ApplyImpulse(sf::Vector2f _dir,
                      float _force);
    void ClearForces();

};

struct Manifold
{
    PhysicsBody& A;
    PhysicsBody& B;

    sf::Vector2f depth;
};