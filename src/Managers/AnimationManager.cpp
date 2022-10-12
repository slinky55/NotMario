#include <Managers/AnimationManager.h>

AnimationManager::AnimationManager(entt::registry &_reg)
:
m_reg(_reg)
{
}

void AnimationManager::Update()
{
    auto view = m_reg.view<AnimationC>();

    for (auto& e : view)
    {
        auto& anim = view.get<AnimationC>(e);
        if (!anim.currentAnimation->play) continue;
        Animation* current = anim.currentAnimation;
        current->currentFrame = static_cast<int>(current->timer / current->frameTime) % current->totalFrames;
        current->timer++;
    }
}

