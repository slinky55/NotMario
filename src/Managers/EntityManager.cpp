#include "Managers/EntityManager.h"

EntityManager::EntityManager(entt::registry& _reg)
:
m_reg(_reg)
{
}

entt::entity EntityManager::Create()
{
    return m_reg.create();
}

RenderableC& EntityManager::AddSprite(entt::entity _ent)
{
    return m_reg.emplace<RenderableC>(_ent);
}

PhysicsC& EntityManager::AddPhysics(entt::entity _ent)
{
    auto& physC = m_reg.emplace<PhysicsC>(_ent);
}
