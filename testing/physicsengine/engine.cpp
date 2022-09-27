#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

constexpr float PIXELS_PER_METER = 16.f;

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

        sf::Vector2f position,
                     velocity,
                     acceleration;

        sf::Vector2f centerOffset;

        AABB collider;

        bool hasGravity {false};

        float invMass {0};
        float mass {0};
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

    class PhysicsEngine
    {
    public:
        PhysicsEngine() = default;
        ~PhysicsEngine();

        PhysicsBody* CreateBody();
        void Update(float _dt);
    private:
        std::vector<PhysicsBody*> m_bodyList;

        bool CheckCollision(const AABB& A,
                            const AABB& B);
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
            body->position += (body->velocity * _dt);
            body->collider.center = body->position;

            body->ClearForces();
        }

        for (uint32_t A = 0; A < m_bodyList.size(); A++)
        {
            for (uint32_t B = 1; B < m_bodyList.size(); B++)
            {
                if (A == B) continue;

                CheckCollision(m_bodyList[A]->collider,
                               m_bodyList[B]->collider);
            }
        }
    }

    bool PhysicsEngine::CheckCollision(const AABB &A,
                                        const AABB &B)
    {
        if ( std::abs(A.center.x - B.center.x) >= A.halfSize.x + B.halfSize.x ) return false;
        if ( std::abs(A.center.y - B.center.y) >= A.halfSize.y + B.halfSize.y ) return false;

        return true;
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

    testEntity.body = physicsEngine.CreateBody();
    testEntity.body->position = {128 / PIXELS_PER_METER, 256 / PIXELS_PER_METER};
    testEntity.body->centerOffset = {16 / PIXELS_PER_METER, 16 / PIXELS_PER_METER};
    testEntity.body->hasGravity = true;
    testEntity.body->SetMass(70.f);
    testEntity.body->collider = {
            {128, 256},
            {16, 16}
    };
    testEntity.rect.setSize({32, 32});
    testEntity.rect.setFillColor(sf::Color::White);

    floor.body = physicsEngine.CreateBody();
    floor.body->position = {400 / PIXELS_PER_METER, (600 - 16) / PIXELS_PER_METER};
    floor.body->centerOffset = {400 / PIXELS_PER_METER, 16 / PIXELS_PER_METER};
    floor.body->collider = {
            {floor.body->position},
            {400, 16}
    };
    floor.rect.setSize({800, 32});
    floor.rect.setFillColor(sf::Color::White);

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
            testEntity.body->ApplyForce({1.f, 0.f}, 1500);
        }

        physicsEngine.Update(clock.restart().asSeconds());

        testEntity.rect.setPosition((testEntity.body->position * PIXELS_PER_METER) -
                                    (testEntity.body->centerOffset * PIXELS_PER_METER));
        floor.rect.setPosition((floor.body->position * PIXELS_PER_METER) -
                               ((floor.body->centerOffset * PIXELS_PER_METER)));

        window.clear();
        window.draw(testEntity.rect);
        window.draw(floor.rect);
        window.display();
    }

    return 0;
}