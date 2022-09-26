#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

constexpr float PIXELS_PER_METER = 16.f;

namespace Physics
{
    struct PhysicsBody
    {
        void ClearForces();
        void ApplyForce(const sf::Vector2f& _direction,
                        float _forceInN);

        sf::Vector2f position,
                     velocity,
                     acceleration;
        float invMass {0};
        float mass {0};
    };

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
        for (auto body : m_bodyList)
        {
            body->ApplyForce({0, 1},
                             9.8f * body->mass);

            body->velocity += (body->acceleration * _dt);
            body->position += (body->velocity * _dt);

            body->ClearForces();
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

    testEntity.body = physicsEngine.CreateBody();
    testEntity.body->position = {128 / PIXELS_PER_METER, 256 / PIXELS_PER_METER};
    testEntity.body->invMass = 1.f / 70.f;
    testEntity.body->mass = 70.f;
    testEntity.rect.setSize({32, 32});
    testEntity.rect.setFillColor(sf::Color::White);

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
            testEntity.body->ApplyForce({1.f, 0.f}, 5.f);
        }

        physicsEngine.Update(clock.restart().asSeconds());

        testEntity.rect.setPosition(testEntity.body->position * PIXELS_PER_METER);

        window.clear();
        window.draw(testEntity.rect);
        window.display();
    }

    return 0;
}