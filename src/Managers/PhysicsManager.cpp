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

    for (auto& A : view) {
        auto& a = m_reg.get<PhysicsC>(A);
        if (a.type == PhysicsType::DYNAMIC)
        {
            a.prevVel = a.vel;
            a.prevPos = a.pos;

            if (!a.onGround)
                a.vel = a.prevVel + (m_gravity * _dt);
            a.pos = a.prevPos + (a.vel * _dt);

            a.collider.center =
                    a.pos + a.collider.centerOffset;
        }
    }

    for (auto& A : view) {
        auto& a = m_reg.get<PhysicsC>(A);
        for (auto& B : view)
        {
            if (A == B) continue;
            auto& b = m_reg.get<PhysicsC>(B);
            AABBDoesCollide(a, b);
        }
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
            _manifold->A.vel.y = 0;
            _manifold->A.onGround = true;
        }
        else
            _manifold->A.pos.y += _manifold->depthY;
    }
//    else
//    {
//        if (_manifold->A.pos.x < _manifold->B.pos.x)
//            _manifold->A.pos.x -= _manifold->depthX;
//        else
//            _manifold->A.pos.x += _manifold->depthX;
//    }

    delete _manifold;
}
