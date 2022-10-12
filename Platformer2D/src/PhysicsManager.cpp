#include "Physics/PhysicsManager.h"

#include <utility>

namespace p2d
{
    PhysicsManager::PhysicsManager(std::shared_ptr<Player> _player)
    :
    m_player(std::move(_player))
    {
    }

    // API
    PhysicsBody* PhysicsManager::Create()
    {
        auto* body = new (m_allocator.Allocate(BODY_SIZE)) (PhysicsBody);
        body->ID = m_bodyCount++;
        return m_bodyList.emplace_front(body);
    }

    void PhysicsManager::Update(float _dt)
    {
        for (auto body : m_bodyList)
        {
            if (body->type == PhysicsType::DYNAMIC)
            {
                if (body->hasGravity)
                    body->ApplyForce(DOWN_NORM,
                                    GRAVITY.y * body->mass);

                body->velocity += (body->acceleration * _dt);
                body->velocity.x *= 0.8f;
                body->position += (body->velocity * _dt);
                body->collider.center = body->position;

                body->ClearForces();
            }
        }

        // Check collisions
        for (auto B : m_bodyList)
        {
            if (B->ID == m_player->m_physComponent->ID) continue;
            CheckCollision(*m_player->m_physComponent,
                           *B);
        }
    }

    // Utility functions
    void PhysicsManager::CheckCollision(PhysicsBody &A, PhysicsBody &B) {
        if ( std::abs(A.collider.center.x - B.collider.center.x) > A.collider.halfSize.x + B.collider.halfSize.x  ||
             std::abs(A.collider.center.y - B.collider.center.y) > A.collider.halfSize.y + B.collider.halfSize.y)
            return;

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
                _manifold->A.collider.center.x = _manifold->A.position.x;
                _manifold->A.velocity.x = 0;
            }
        }
        else
        {
            _manifold->A.position -= _manifold->depth;
        }

        delete _manifold;
    }

}