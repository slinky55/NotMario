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

    sf::Vector2f centerOffset;

    AABB collider;

    bool hasGravity {false};

    float invMass {0};
    float mass {0};
};




//struct PhysicsC
//{
//    sf::Vector2f prevPos;
//    sf::Vector2f pos;
//
//    sf::Vector2f prevVel;
//    sf::Vector2f vel;
//
//    sf::Vector2f size;
//
//    float mass;
//
//    AABB collider;
//
//    PhysicsType type;
//};

struct Manifold
{
    PhysicsBody& A;
    PhysicsBody& B;

    sf::Vector2f depth;
};