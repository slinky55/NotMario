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
    auto view = m_reg.view<PhysicsBody>();

    // Move dynamic objects
    for (auto& A : view)
    {
        auto& a = m_reg.get<PhysicsBody>(A);
        if (a.type == PhysicsType::DYNAMIC)
        {
            ApplyForce(a,
                       DOWN_NORM,
                       9.8f * a.mass);

            a.velocity += (a.acceleration * _dt);
            a.position += (a.velocity * _dt);

            a.collider.center =
                    a.position + a.collider.halfSize;

            ClearForces(a);
        }
    }

    // Check collisions
    for (auto& other : view) {
        if (other == m_player.m_ID) continue;
        auto& otherP = m_reg.get<PhysicsBody>(other);
        CheckCollision(*m_player.m_physComponent,
                        otherP);
    }
}

void PhysicsManager::SetMass(PhysicsBody &_body,
                             float _mass)
{
    _body.invMass = 1 / _mass;
    _body.mass = _mass;
}

void PhysicsManager::ApplyForce(PhysicsBody &_body,
                                sf::Vector2f _dir,
                                float _forceInN)
{
    _body.acceleration += (_dir * (_forceInN * _body.invMass));
}
void PhysicsManager::ClearForces(PhysicsBody &_body)
{
    _body.acceleration = {0, 0};
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
