#pragma once

#include <entt/entity/registry.hpp>

class EntityManager
{
public:
    EntityManager(entt::registry& _reg);

    entt::entity Create();
private:
    entt::registry& m_reg;
};
