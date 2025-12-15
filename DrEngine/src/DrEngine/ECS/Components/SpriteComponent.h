#pragma once

#include "../ECS.h"

#include "SDL_image.h"

namespace DrEngine::ECS
{
    class DRENGINE_API SpriteComponent : public Component
    {
    public:
        SpriteComponent(const std::string& img_path)
        {
            texture = new Texture(img_path);
        }
        
        ~SpriteComponent()
        {
            texture->Destroy();
        }

        void BeginPlay() override
        {
            transform = GetOwner()->GetComponentByClass<TransformComponent>();
            if (!transform)
            {
                DE_ERROR("Transform component not found for SpriteComponent on Entity {0}", GetOwner()->GetName());
            }
        }

        void Draw(float deltaTime) override
        {
            if (texture)
            {
                Application::GetRenderer()->RenderTexture(transform->GetLocation(), transform->GetScale(), texture, nullptr, flip);
            }
            else
            {
                DE_ERROR("texture not valid!");
            }
        }

        void SetFlip(TextureFlip inFlip) { flip = inFlip; };
        
    private:

        TextureFlip flip{None};
        
        TransformComponent* transform{nullptr};

        Texture* texture;
    };
}