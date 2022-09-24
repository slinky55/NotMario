#pragma once

#include <SFML/System/Vector2.hpp>

struct AABB
{
    sf::Vector2f center;
    sf::Vector2f halfSize;

    sf::Vector2f centerOffset;
};

struct PhysicsObject
{
    sf::Vector2f prevPos;
    sf::Vector2f pos;

    sf::Vector2f prevVel;
    sf::Vector2f vel;

    sf::Vector2f size;

    AABB collider;

    bool pushedRight = false;
    bool pushesRight = false;

    bool pushedLeft = false;
    bool pushesLeft = false;

    bool onGround = false;
    bool wasOnGround = false;

    bool atCeiling = false;
    bool wasAtCeiling = false;

    bool isDynamic = false;

    bool jump = false;
};