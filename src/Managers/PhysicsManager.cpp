#include "Managers/PhysicsManager.h"

PhysicsManager::PhysicsManager(entt::registry &_reg)
    :
    m_reg(_reg)
{
    m_world = new b2World {{0.f, 9.8f}};
}

b2Body* PhysicsManager::RegisterBody(b2BodyDef *_bodyDef)
{
    return m_world->CreateBody(_bodyDef);
}

void PhysicsManager::Update(float _dt)
{
    m_world->Step(_dt, 8, 3);
}
