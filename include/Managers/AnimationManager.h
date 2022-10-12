#pragma once

#include <Components/AnimationC.h>
#include <entt/entity/registry.hpp>

class AnimationManager
{
public:
    explicit AnimationManager(entt::registry& _reg);

    void Update();
private:
    entt::registry& m_reg;
};