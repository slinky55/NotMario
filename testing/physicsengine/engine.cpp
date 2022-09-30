#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

constexpr float PIXELS_PER_METER {16.f};
constexpr sf::Vector2f GRAVITY = {0, 1.62f};

namespace Physics
{
    struct AABB
    {
        sf::Vector2f center;
        sf::Vector2f halfSize;
    };

    struct PhysicsBody
    {
        void SetMass(float _mass);

        void ClearForces();
        void ApplyForce(const sf::Vector2f& _direction,
                        float _forceInN);
        void ApplyImpulse(const sf::Vector2f& _direction,
                          float _impulse);

        sf::Vector2f position,
                     velocity,
                     acceleration;

        sf::Vector2f centerOffset;

        AABB collider;

        bool hasGravity {false};
        bool onGround {false};

        float invMass {0};
        float mass {0};
    };

    struct Manifold
    {
        PhysicsBody& A;
        PhysicsBody& B;

        sf::Vector2f depth;
    };

    void PhysicsBody::SetMass(float _mass)
    {
        invMass = 1 / _mass;
        mass = _mass;
    }
    void PhysicsBody::ClearForces() { acceleration = {0, 0}; }
    void PhysicsBody::ApplyForce(const sf::Vector2f& _direction,
                                   float _forceInN)
    {
        acceleration += (_direction * (_forceInN * invMass));
    }
    void PhysicsBody::ApplyImpulse(const sf::Vector2f& _direction,
                                   float _impulse)
    {
        velocity += (_direction * (_impulse * invMass));
    }

    class PhysicsEngine
    {
    public:
        PhysicsEngine() = default;
        ~PhysicsEngine();

        PhysicsBody* CreateBody();
        void Update(float _dt);
    private:
        std::vector<PhysicsBody*> m_bodyList;

        void CheckCollision(PhysicsBody& A,
                            PhysicsBody& B);
        void ResolveCollision(Manifold* _manifold);
    };

    PhysicsEngine::~PhysicsEngine()
    {
        for (auto body : m_bodyList)
        {
            delete body;
        }
    }

    PhysicsBody* PhysicsEngine::CreateBody()
    {
        return m_bodyList.emplace_back(new PhysicsBody{});
    }

    void PhysicsEngine::Update(float _dt)
    {
        // Update bodies
        for (auto body : m_bodyList)
        {
            if (body->hasGravity)
                body->ApplyForce({0, 1},
                             9.8f * body->mass);
            body->velocity += (body->acceleration * _dt);
            body->velocity.y = std::min(60.f, body->velocity.y);    // Terminal velocity
            body->position += (body->velocity * _dt);
            body->collider.center = body->position;

            body->ClearForces();
        }

        for (uint32_t A = 0; A < m_bodyList.size(); A++)
        {
            for (uint32_t B = 1; B < m_bodyList.size(); B++)
            {
                if (A == B) continue;

                CheckCollision(*m_bodyList[A],
                               *m_bodyList[B]);
            }
        }
    }

    void PhysicsEngine::CheckCollision(PhysicsBody &A,
                                       PhysicsBody &B)
    {
        if ( std::abs(A.collider.center.x - B.collider.center.x) >= A.collider.halfSize.x + B.collider.halfSize.x ) return;
        if ( std::abs(A.collider.center.y - B.collider.center.y) >= A.collider.halfSize.y + B.collider.halfSize.y ) return;

        ResolveCollision(new Manifold{
            A, B,
            {
                ((A.collider.halfSize.x + B.collider.halfSize.x) -
                  std::abs(A.collider.center.x - B.collider.center.x)),
                ((A.collider.halfSize.y + B.collider.halfSize.y) -
                  std::abs(A.collider.center.y - B.collider.center.y))
            }
        });
    }

    void PhysicsEngine::ResolveCollision(Manifold *_manifold)
    {
        if (_manifold->depth.x > _manifold->depth.y)
        {
            if (_manifold->A.position.y < _manifold->B.position.y)
            {
                _manifold->A.position.y -= _manifold->depth.y;
                _manifold->A.collider.center.y -= _manifold->depth.y;
                _manifold->A.onGround = true;
            }
            else if (_manifold->A.position.y > _manifold->B.position.y)
            {
                _manifold->A.position.y += _manifold->depth.y;
                _manifold->A.collider.center.y += _manifold->depth.y;
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
    }
}

struct Entity
{
    sf::RectangleShape rect;
    Physics::PhysicsBody* body;
};

int main()
{
    sf::RenderWindow window { sf::VideoMode{ {800, 600} }, "Physics Engine Test" };
    assert(window.isOpen());

    sf::Clock clock;

    Physics::PhysicsEngine physicsEngine {};
    Entity testEntity;
    Entity floor;
    Entity box;

    // Apollo 11
    testEntity.body = physicsEngine.CreateBody();
    testEntity.body->position = {128 / PIXELS_PER_METER, 256 / PIXELS_PER_METER};
    testEntity.body->centerOffset = {16 / PIXELS_PER_METER, 16 / PIXELS_PER_METER};
    testEntity.body->hasGravity = true;
    testEntity.body->SetMass(5000.f);
    testEntity.body->collider = {
            testEntity.body->position,
            testEntity.body->centerOffset
    };
    testEntity.rect.setSize({32, 32});
    testEntity.rect.setFillColor(sf::Color::Red);

    floor.body = physicsEngine.CreateBody();
    floor.body->position = {400 / PIXELS_PER_METER, (600 - 16) / PIXELS_PER_METER};
    floor.body->centerOffset = {400 / PIXELS_PER_METER, 16 / PIXELS_PER_METER};
    floor.body->collider = {
            floor.body->position,
            floor.body->centerOffset
    };
    floor.rect.setSize({800, 32});
    floor.rect.setFillColor(sf::Color::White);

    box.body = physicsEngine.CreateBody();
    box.body->position = { 400 / PIXELS_PER_METER, (600 - 48) / PIXELS_PER_METER };
    box.body->centerOffset = {16 / PIXELS_PER_METER, 16 / PIXELS_PER_METER};
    box.body->collider = {
            box.body->position,
            box.body->centerOffset
    };
    box.rect.setSize({32, 32});
    box.rect.setFillColor(sf::Color::Blue);

    while (window.isOpen())
    {
        sf::Event e{};
        while(window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            testEntity.body->ApplyForce({1.f, 0.f}, 1500.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            testEntity.body->ApplyForce({-1.f, 0.f}, 1500.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            testEntity.body->ApplyForce({0.f, -1.f}, 3000.f);
        }

        physicsEngine.Update(clock.restart().asSeconds());

        testEntity.rect.setPosition((testEntity.body->position * PIXELS_PER_METER) -
                                    (testEntity.body->centerOffset * PIXELS_PER_METER));
        floor.rect.setPosition((floor.body->position * PIXELS_PER_METER) -
                               ((floor.body->centerOffset * PIXELS_PER_METER)));
        box.rect.setPosition((box.body->position * PIXELS_PER_METER) -
                             ((box.body->centerOffset * PIXELS_PER_METER)));

        window.clear();
        window.draw(testEntity.rect);
        window.draw(floor.rect);
        window.draw(box.rect);
        window.display();
    }

    return 0;
}