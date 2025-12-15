#pragma once

#include <SDL_rect.h>

#include "Core.h"
#include "Enums.h"
#include "Math/Vector2D.h"

struct SDL_Renderer;

namespace DrEngine
{
    class Window;
    struct Color;
    struct Texture;
    
    class DRENGINE_API Renderer
    {
    public:
        Renderer();
        ~Renderer();

        bool Initialize(Window* window);

        void RenderRect(const Vector2D& Location, const Vector2D& Scale, const Color& color);
        void RenderTexture(const Vector2D& Location, const Vector2D& Scale, const Texture* texture, const SDL_Rect* inSrcRect = nullptr, TextureFlip inFlip = None);
        void RenderPoint(const Vector2D& Location);
    
        SDL_Renderer* GetSDLRenderer() const { return SDLrenderer; };
    
    private:
        SDL_Renderer* SDLrenderer;
    };
}
