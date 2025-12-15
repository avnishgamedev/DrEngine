#pragma once

#include "DrEngine.h"
#include "Components/NotificationComp.h"

using namespace DrEngine;

class Ball : public Entity
{
public:
    Ball(const std::vector<Entity*>& inPaddles, const std::string& inName = "Ball") : Entity(inName)
    {
        transform = AddComponent<TransformComponent>();
        transform->Location = Vector2D(280, 280);
        transform->Scale = Vector2D(36, 36);
        AddComponent<RectComp>()->SetVisibility(false);
        AddComponent<TextComp>("Assets/Fonts/Sans.ttf", 28, "Score: 0");
        AddComponent<SpriteComponent>("Assets/Images/ball.png");
        AddComponent<CollisionComponent>()->AddCallback(this, &Ball::OnCollision);

        paddles = inPaddles;
        now = Application::GetMilliseconds();
    }
    
    ~Ball()
    {
        
    }

    void BeginPlay() override
    {
        Entity::BeginPlay();
        
        transform->Velocity = Vector2D(0.28f, -0.28f);
        
        boing = new Audio("Assets/Audio/boing.wav");
        reset = new Audio("Assets/Audio/reset.wav");
    }

    void Update(float deltaTime) override
    {
        Entity::Update(deltaTime);

        now = Application::GetMilliseconds();
        
        if (now - last > 100)
        {
            if (transform->GetLocation().X() > 800)
            {
                transform->Location.SetX(800);
                transform->Velocity.SetX(transform->GetVelocity().X() * -1);
                last = now;
                Score = 0;

                Application::manager->AddEntity()->AddComponent<NotificationComp>("Score Reset!", 1000);

                reset->PlayAudio();
            }
            if (transform->GetLocation().X() < 0)
            {
                transform->Location.SetX(0);
                transform->Velocity.SetX(transform->GetVelocity().X() * -1);
                last = now;
                Score = 0;

                Application::manager->AddEntity()->AddComponent<NotificationComp>("Score Reset!", 1000);

                reset->PlayAudio();
            }
            if (transform->GetLocation().Y() > 580)
            {
                transform->Location.SetY(580);
                transform->Velocity.SetY(transform->GetVelocity().Y() * -1);
                last = now;
            }
            if (transform->GetLocation().Y() < 0)
            {
                transform->Location.SetY(0);
                transform->Velocity.SetY(transform->GetVelocity().Y() * -1);
                last = now;
            }
        }
    }

    void OnCollision(const CollisionData& inData)
    {
        if (Application::GetMilliseconds() - last > 100)
        {
            for (const auto p : paddles)
            {
                if (inData.OtherEntity == p)
                {
                    transform->Velocity.SetX(transform->GetVelocity().X() * -1);
                    last = now;
                    Score++;
                    if (boing->IsValid())
                    {
                        boing->PlayAudio();
                    }
                    
                    break;
                }
            }
        }
    }

    int GetScore() const { return Score; };
    
private:
    Audio* boing{nullptr};
    Audio* reset{nullptr};
    
    int Score{0};
    
    Uint32 last, now;
    
    std::vector<Entity*> paddles;
    TransformComponent* transform;
};