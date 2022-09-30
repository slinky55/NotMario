#include "Managers/PhysicsManager.h"

#include <utility>

PhysicsManager::PhysicsManager(entt::registry &_reg,
                               std::shared_ptr<Player> _player)
    :
    m_reg(_reg),
    m_player(std::move(_player))
{
}

void PhysicsManager::Update(float _dt)
{
    auto view = m_reg.view<PhysicsBody>();

    // Move dynamic objects
    for (auto& A : view)
    {
        auto& a = m_reg.get<PhysicsBody>(A);
        if (a.type == PhysicsType::DYNAMIC)
        {
            if (a.hasGravity)
            {
                a.ApplyForce(DOWN_NORM,
                             GRAVITY.y * a.mass);
            }

            a.velocity += (a.acceleration * _dt);

            if (!a.onGround)
                a.velocity.x *= (1 - DAMPING_CONSTANT);
            else
                a.velocity.x *= (1 - FRICTION_CONSTANT);

            a.position += ((a.velocity) * _dt);

            a.collider.center = a.position;

            a.ClearForces();
        }
    }

    // Check collisions
    for (auto& other : view) {
        if (other == m_player->ID) continue;
        auto& otherP = m_reg.get<PhysicsBody>(other);
        CheckCollision(*m_player->m_physComponent,
                        otherP);
    }
}

void PhysicsManager::CheckCollision(PhysicsBody &A, PhysicsBody &B) {
    if ( std::abs(A.collider.center.x - B.collider.center.x) >= A.collider.halfSize.x + B.collider.halfSize.x ) return;
    if ( std::abs(A.collider.center.y - B.collider.center.y) >= A.collider.halfSize.y + B.collider.halfSize.y ) return;

    ResolveCollision(new Manifold{
                           A, B,
                           {(A.collider.halfSize.x + B.collider.halfSize.x) -
                          (std::abs(A.collider.center.x - B.collider.center.x)),
                          (A.collider.halfSize.y + B.collider.halfSize.y) -
                          (std::abs(A.collider.center.y - B.collider.center.y))}
    });
}

void PhysicsManager::ResolveCollision(Manifold* _manifold)
{
    if (_manifold->depth.x > _manifold->depth.y)
    {
        if (_manifold->A.position.y < _manifold->B.position.y)
        {
            _manifold->A.position.y -= _manifold->depth.y;
            _manifold->A.collider.center.y -= _manifold->depth.y;
            _manifold->A.velocity.y = 0;
            _manifold->A.onGround = true;
        }
        else if (_manifold->A.position.y > _manifold->B.position.y)
        {
            _manifold->A.position.y += _manifold->depth.y;
            _manifold->A.collider.center.y += _manifold->depth.y;
            _manifold->A.velocity.y = 0;
            //_manifold->onCeiling = true;
        }
    }
    else if (_manifold->depth.x < _manifold->depth.y)
    {
        if (_manifold->A.position.x < _manifold->B.position.x)
        {
            _manifold->A.position.x -= _manifold->depth.x;
            _manifold->A.collider.center.x -= _manifold->depth.x;
            _manifold->A.velocity.x = 0;
        }
        else if (_manifold->A.position.x > _manifold->B.position.x)
        {
            _manifold->A.position.x += _manifold->depth.x;
            _manifold->A.collider.center.x += _manifold->depth.x;
            _manifold->A.velocity.x = 0;
        }
    }
    else
    {
        _manifold->A.position -= _manifold->depth;
    }

    delete _manifold;
}
