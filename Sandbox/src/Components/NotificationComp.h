#pragma once

#include "DrEngine.h"

using namespace DrEngine::ECS;

class NotificationComp : public Component
{
public:
    NotificationComp(const std::string& notificationMessage, int inDuration = 4000, Vector2D inLoc = Vector2D(500, 40))
    {
        message = notificationMessage;
        duration = inDuration;
        Location = inLoc;
    }

    void BeginPlay() override
    {
        const auto textComp = GetOwner()->AddComponent<TextComp>("Assets/Fonts/Sans.ttf", 28, message);
        textComp->SetLocation(Location);
        StartTime = Application::GetMilliseconds();
    }
    
    void Update(float deltaTime) override
    {
        if (Application::GetMilliseconds() - StartTime > static_cast<Uint32>(duration))
        {
            Entity* owner = GetOwner();
            Application::manager->DestroyEntity(owner);
        }
    }
private:

    std::string message;
    int duration{0};
    Vector2D Location{Vector2D::Zero()};
    
    Uint32 StartTime;
};