#include "Managers/EntityManager.h"

EntityManager::EntityManager(entt::registry& _reg)
:
m_reg(_reg)
{
}

entt::entity EntityManager::Register()
{
    return m_reg.create();
}

p2d::PhysicsBody& EntityManager::AddPhysicsComponent(entt::entity &_ent) {
    return m_reg.emplace<p2d::PhysicsBody>(_ent);
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

AnimationC& EntityManager::AddAnimationComponent(entt::entity &_ent)
{
    return m_reg.emplace<AnimationC>(_ent);
}

entt::entity EntityManager::CreateBlock(const sf::Vector2f &_pos,
                                        const sf::Vector2f &_size,
                                        const sf::Color &_color)
{
    auto block = Register();
    auto& blockP = AddPhysicsComponent(block);
    auto& blockR = AddRectangleComponent(block);

    blockP.position = {
        (_pos / PIXELS_PER_METER).x,
        (_pos / PIXELS_PER_METER).y
    };
    blockP.halfSize = {
        ((_size / 2.f) / PIXELS_PER_METER).x,
        ((_size / 2.f) / PIXELS_PER_METER).y
    };
    blockP.collider = {
            blockP.position,
            blockP.halfSize
    };
    blockR.rect.setSize(_size);
    blockR.rect.setFillColor(_color);
    p2d::Vector2 pos = ((blockP.position - blockP.halfSize) * PIXELS_PER_METER);
    blockR.rect.setPosition({pos.x, pos.y});

    return block;
}
