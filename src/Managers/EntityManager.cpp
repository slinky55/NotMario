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

PhysicsBody& EntityManager::AddPhysicsComponent(entt::entity &_ent) {
    return m_reg.emplace<PhysicsBody>(_ent);
}


SpriteC& EntityManager::AddSpriteComponent(entt::entity& _ent)
{
    return m_reg.emplace<SpriteC>(_ent);
}

RectangleC& EntityManager::AddRectangleComponent(entt::entity& _ent)
{
    return m_reg.emplace<RectangleC>(_ent);
}

InputC& EntityManager::AddInputComponent(entt::entity& _ent)
{
    return m_reg.emplace<InputC>(_ent);
}