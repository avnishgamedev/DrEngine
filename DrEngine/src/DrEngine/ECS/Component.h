#pragma once

#include "ECS.h"

namespace DrEngine::ECS
{
    class Entity;
    
    class DRENGINE_API Component
    {
    public:
        Component()
        {
        }

        virtual ~Component()
        {
            
        }

        virtual void BeginPlay()
        {
            
        }

        virtual void Update(float deltaTime)
        {
            
        }

        virtual void Draw(float deltaTime)
        {
            
        }

        Entity* GetOwner() const { return owner; };
        
        Entity* owner;
    };
}
