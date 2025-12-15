#pragma once

#include "../Component.h"
#include "../../Math/Vector2D.h"

namespace DrEngine::ECS
{
    class DRENGINE_API TransformComponent : public Component
    {
    public:
        TransformComponent(Vector2D Loc = Vector2D::Zero(), Vector2D Sc = Vector2D::Zero(), Vector2D Vel = Vector2D::Zero())
        {
            Location = Loc;
            Scale = Sc;
            Velocity = Vel;
        }

        ~TransformComponent() override
        {
            
        }

        void Update(float deltaTime) override
        {
            Location += Velocity * deltaTime;
        }

        void SetLocation(Vector2D inVal) { Location = inVal; };
        void SetScale(Vector2D inVal) { Scale = inVal; };
        void SetVelocity(Vector2D inVal) { Velocity = inVal; };
        
        Vector2D GetLocation() const { return Location; };
        Vector2D GetScale() const { return Scale; };
        Vector2D GetVelocity() const { return Velocity; };

        Vector2D Location;
        Vector2D Scale;
        Vector2D Velocity;
    };
}
