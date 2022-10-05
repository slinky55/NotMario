#pragma once

#include "Managers/EntityManager.h"
#include "Managers/InputManager.h"
#include "Physics/PhysicsManager.h"
#include "Managers/RenderManager.h"
#include "Managers/ResourceManager.h"

class Scene
{
public:
    Scene(EntityManager& _entityMgr,
          InputManager& _inputMgr,
          PhysicsManager& _physicsMgr,
          RenderManager& _renderMgr,
          ResourceManager& _resourceMgr);

    virtual void OnCreate() = 0;
    virtual void OnDestroy() = 0;

    virtual void Update(float _dt) = 0;
    virtual void Draw() = 0;
private:
    EntityManager& m_entityMgr;
    InputManager& m_inputMgr;
    PhysicsManager& m_physicsMgr;
    RenderManager& m_renderMgr;
    ResourceManager& m_resourceMgr;
};