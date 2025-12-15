#pragma once

#include "../ECS.h"

namespace DrEngine::ECS
{
    class DRENGINE_API AnimationComp : public Component
    {
    public:
        AnimationComp(const std::string& inFilePath, int inAnimFrameDelay = 10, int inNoFrames = 3)
        {
            filePath = inFilePath;
            animFrameDelay = inAnimFrameDelay;
            noFrames = inNoFrames;
        }

        ~AnimationComp()
        {
            tex->Destroy();
            transform = nullptr;
        }

        void BeginPlay() override
        {
            transform = GetOwner()->GetComponentByClass<TransformComponent>();
            if (!transform)
            {
                DE_ERROR("Transform component not found for AnimationComp on Entity {0}", GetOwner()->GetName());
            }

            tex = new Texture(filePath);
            
            int x, y;
            SDL_QueryTexture(tex->GetSDLTexture(), nullptr, nullptr, &x, &y);
            frameSize = x / noFrames;
            srcRect.w = frameSize;
        }

        void Draw(float deltaTime) override
        {
            srcRect.x = frameSize * static_cast<int>((Application::GetMilliseconds() / animFrameDelay) % noFrames);
            Application::GetRenderer()->RenderTexture(transform->GetLocation(), transform->GetScale(), tex, &srcRect);
        }

    private:
        TransformComponent* transform;
        
        std::string filePath;
        int frameSize;
        int animFrameDelay;
        int noFrames;

        SDL_Rect srcRect;

        Texture* tex;
    };
}