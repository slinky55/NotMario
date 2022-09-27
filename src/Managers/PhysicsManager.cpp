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

    for (auto& A : view)
    {
        auto& a = m_reg.get<PhysicsC>(A);
        if (a.type == PhysicsType::DYNAMIC)
        {
            a.prevVel = a.vel;
            a.prevPos = a.pos;

            a.vel = a.prevVel + (m_gravity * _dt);
            a.pos = a.prevPos + (a.vel * _dt);

            a.collider.center =
                    a.pos + a.collider.centerOffset;
        }
    }

    for (auto& other : view) {
        if (other == m_player.m_ID) continue;
        auto& otherP = m_reg.get<PhysicsC>(other);
        AABBDoesCollide(*m_player.m_physComponent,
                        otherP);
    }
}

void PhysicsManager::AABBDoesCollide(PhysicsC &A,
                                     PhysicsC &B)
{
    if ( std::abs(A.collider.center.x - B.collider.center.x) >= A.collider.halfSize.x + B.collider.halfSize.x ) return;
    if ( std::abs(A.collider.center.y - B.collider.center.y) >= A.collider.halfSize.y + B.collider.halfSize.y ) return;

    ResolveCollision(new Manifold{A, B,
                          (A.collider.halfSize.x + B.collider.halfSize.x) -
                          (std::abs(A.collider.center.x - B.collider.center.x)),

                          (A.collider.halfSize.y + B.collider.halfSize.y) -
                          (std::abs(A.collider.center.y - B.collider.center.y))});
}

void PhysicsManager::ResolveCollision(Manifold* _manifold)
{
    if (_manifold->depthX > _manifold->depthY)
    {
        if (_manifold->A.pos.y < _manifold->B.pos.y)
        {
            _manifold->A.pos.y -= _manifold->depthY;
            _manifold->A.collider.center.y -= _manifold->depthY;
        }
        else
        {

        }
    }
    else
    {

    }

    delete _manifold;
}
