#pragma once

#include "DrEngine.h"

using namespace DrEngine;

class Paddle : public Entity
{
public:
    Paddle(const Vector2D& inLoc = Vector2D::Zero(), const Color& inColor = Color(0, 0, 255) ,const std::string& inName = "Paddle") : Entity(inName)
    {
        transform = AddComponent<TransformComponent>();
        transform->Location = inLoc;
        transform->Scale = Vector2D(10, 100);
        AddComponent<RectComp>(inColor);
        AddComponent<CollisionComponent>();
    }
    
    ~Paddle()
    {
        
    }

    void BeginPlay() override
    {
        Entity::BeginPlay();
        
    }

    void Update(float deltaTime) override
    {
        Entity::Update(deltaTime);

        transform->Location = Vector2D(transform->GetLocation().X(), Application::GetInputManager()->GetMousePos().Y());
    }

private:

    TransformComponent* transform;
};