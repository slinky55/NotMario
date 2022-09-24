#pragma once

#include <box2d/box2d.h>
#include <entt/entity/registry.hpp>

class PhysicsManager
{
public:
    explicit PhysicsManager(entt::registry& _reg);

    b2Body* RegisterBody(b2BodyDef* _bodyDef);
    void Update(float _dt);
private:
    entt::registry& m_reg;

    b2World* m_world;
};