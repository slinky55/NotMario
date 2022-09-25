#pragma once

#include <SFML/System/Vector2.hpp>

struct AABB
{
    sf::Vector2f center;
    sf::Vector2f halfSize;
    sf::Vector2f centerOffset;
};

struct PhysicsC
{
    sf::Vector2f prevPos;
    sf::Vector2f pos;

    sf::Vector2f prevVel;
    sf::Vector2f vel;

    sf::Vector2f size;

    AABB collider;
};