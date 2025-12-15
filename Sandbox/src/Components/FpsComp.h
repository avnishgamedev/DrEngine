#pragma once

#include "DrEngine.h"

using namespace DrEngine::ECS;

class FpsComp : public Component
{
public:
    void BeginPlay() override
    {
        
    }

    void Update(float deltaTime) override
    {
        auto msec = Application::GetMilliseconds() - startTime;
        startTime = Application::GetMilliseconds();
        if(msec > 0)
            fps = 1000.0f / static_cast<float>(msec);
    }

    float GetFPS() const { return fps; };
private:
    float fps{0};
    Uint32 startTime = Application::GetMilliseconds();
    
};