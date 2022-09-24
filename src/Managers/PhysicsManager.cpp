#include "Managers/PhysicsManager.h"

PhysicsManager::PhysicsManager(entt::registry &_reg,
                               entt::entity& _player)
    :
    m_reg(_reg),
    m_player(_player)
{
}

void PhysicsManager::Update(float _dt)
{
    auto view = m_reg.view<PhysicsObject>();
    auto& playerP = view.get<PhysicsObject>(m_player);

    playerP.prevPos = playerP.pos;
    playerP.prevVel = playerP.vel;

    /*playerP.wasOnGround = playerP.onGround;
    playerP.pushedRight = playerP.pushesRight;
    playerP.pushedLeft = playerP.pushesLeft;
    playerP.wasAtCeiling = playerP.atCeiling;*/

    playerP.vel += ((m_gravity * 35.f) * _dt);

    if (playerP.jump)
    {
        playerP.vel = UP_NORM * 185.f;
        playerP.onGround = false;
    }

    playerP.pos += (playerP.vel * _dt);

    playerP.collider.center = playerP.pos + playerP.collider.centerOffset;

    for (auto& entity : view)
    {
        if (entity != m_player)
        {
            auto& entityP = m_reg.get<PhysicsObject>(entity);
            if (AABBDoesCollide(playerP, entityP))
            {
                ResolveCollision(playerP, entityP);
            }
        }
    }
}

bool PhysicsManager::AABBDoesCollide(const PhysicsObject &A,
                                     const PhysicsObject &B)
{
    if ( std::abs(A.collider.center.x - B.collider.center.x) > A.collider.halfSize.x + B.collider.halfSize.x ) return false;
    if ( std::abs(A.collider.center.y - B.collider.center.y) > A.collider.halfSize.y + B.collider.halfSize.y ) return false;
    return true;
}

void PhysicsManager::ResolveCollision(PhysicsObject& _player,
                                      PhysicsObject& _entity)
{
    if (_player.vel.y > 0)
    {
        _player.pos.y = _player.prevPos.y;
        _player.onGround = true;
    }
}
