#include "Managers/PhysicsManager.h"

PhysicsManager::PhysicsManager(entt::registry &_reg,
                              Player& _player)
    :
    m_reg(_reg),
    m_player(_player)
{
}

void PhysicsManager::Update(float _dt)
{
    auto view = m_reg.view<PhysicsC>();

    for (auto& entity : view) {
        auto &physC = m_reg.get<PhysicsC>(entity);

        if (entity == m_player.m_ID)
        {
            m_player.m_physComponent->vel += ((m_gravity * 20.f) * _dt);
            m_player.m_physComponent->pos += (m_player.m_physComponent->vel * _dt);
            continue;
        }

        if (AABBDoesCollide(*m_player.m_physComponent,
                            physC))
            ResolveCollision(*m_player.m_physComponent,
                             physC);
    }
}

bool PhysicsManager::AABBDoesCollide(const PhysicsC &A,
                                     const PhysicsC &B)
{
    if ( std::abs(A.collider.center.x - B.collider.center.x) > A.collider.halfSize.x + B.collider.halfSize.x ) return false;
    if ( std::abs(A.collider.center.y - B.collider.center.y) > A.collider.halfSize.y + B.collider.halfSize.y ) return false;
    return true;
}

void PhysicsManager::ResolveCollision(PhysicsC& _player,
                                      PhysicsC& _entity)
{
    if (_player.pos.y < _entity.pos.y ||
        _player.pos.y > _entity.pos.y)
    {
        _player.pos.y = _player.prevPos.y;
    }
    else if (_player.pos.x < _entity.pos.x ||
             _player.pos.x > _entity.pos.x)
    {
        _player.pos.x = _player.prevPos.x;
    }
}
