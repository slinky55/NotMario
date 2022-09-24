#pragma once

#include <box2d/box2d.h>

constexpr float PHYS_COORD_CONVERSION = 30.f;

struct PhysicsC
{
    b2BodyDef bodyDef;
    b2Body* body{nullptr};
    b2PolygonShape box;
    b2FixtureDef fixture;
};