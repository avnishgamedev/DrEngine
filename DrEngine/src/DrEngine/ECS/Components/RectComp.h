#pragma once

#include <SDL_rect.h>
#include <SDL_render.h>

#include "TransformComponent.h"
#include "../ECS.h"

namespace DrEngine::ECS
{
    class DRENGINE_API RectComp : public Component
    {
    public:

        RectComp(bool inPulse)
        {
            bPulse = inPulse;
        }
        
        RectComp(const Color& inColor = Color(0, 0, 0, 0))
        {
            color = inColor;
        }
        
        ~RectComp()
        {
            
        }

        void BeginPlay() override
        {
            transform = GetOwner()->GetComponentByClass<TransformComponent>();
            if (!transform)
            {
                DE_ERROR("Transform component not found for RectComp on Entity {0}", GetOwner()->GetName());
            }
        }

        void Draw(float deltaTime) override
        {
            if (bPulse)
            {
                color.SetR(0);
                color.SetG(SDL_fabsf(SDL_cosf(static_cast<float>(SDL_GetTicks()) / 1000.0f) * 255.0f));
                color.SetB(SDL_fabsf(SDL_sinf(static_cast<float>(SDL_GetTicks()) / 1000.0f) * 255.0f));
            }

            if (bVisible)
            {
                Application::GetRenderer()->RenderRect(transform->GetLocation(), transform->GetScale(), color);
            }
        }

        void SetVisibility(bool inVal) { bVisible = inVal; };
        
    private:

        bool bVisible{true};
        bool bPulse{false};
        
        Color color;
        
        TransformComponent* transform;
    };
}
