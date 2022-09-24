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

    playerP.wasOnGround = playerP.onGround;
    playerP.pushedRight = playerP.pushesRight;
    playerP.pushedLeft = playerP.pushesLeft;
    playerP.wasAtCeiling = playerP.atCeiling;

    playerP.vel += ((m_gravity * 35.f) * _dt);

    if (playerP.jump)
    {
        sf::Vector2f up {0, -1};
        playerP.vel = up * 120.f;
        //playerP.vel += (up * 9.8f * 10.f * _dt);
        playerP.jump = false;
    }

    playerP.pos += (playerP.vel * _dt);

    playerP.collider.center = playerP.pos + playerP.collider.centerOffset;

    for (auto& entity : view)
    {
        if (entity != m_player)
        {
            auto& phys = m_reg.get<PhysicsObject>(entity);
            if (AABBDoesCollide(playerP.collider, phys.collider)) {
                playerP.vel.y = 0;
                playerP.onGround = true;
            }
        }
    }
}

bool PhysicsManager::AABBDoesCollide(const AABB &A,
                                     const AABB &B)
{
    if ( std::abs(A.center.x - B.center.x) > A.halfSize.x + B.halfSize.x ) return false;
    if ( std::abs(A.center.y - B.center.y) > A.halfSize.y + B.halfSize.y ) return false;
    return true;
}
