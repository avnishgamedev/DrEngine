#pragma once

#include "../ECS.h"
#include "SDL_ttf.h"
#include "../../Math/Math.h"

namespace DrEngine::ECS
{
    class DRENGINE_API TextComp : public Component
    {
    public:
        TextComp(const std::string& font_path, int font_size, const std::string& message, const Vector2D& inLoc = Vector2D(20, 20), const Color& color = Color(0, 0, 255))
        {
            fontPath = font_path;
            fontSize = font_size;
            text = message;
            textColor = color;
            Location = inLoc;

            RefreshTexture();
        }

        ~TextComp()
        {
            textTexture->Destroy();
        }

        void Draw(float deltaTime) override
        {
            if (bPulse)
            {
                Color color;
                color.SetR(0);
                color.SetG(Math::AbsF(Math::CosF(static_cast<float>(Application::GetMilliseconds()) / 1000.0f) * 255.0f));
                color.SetB(Math::AbsF(Math::SinF(static_cast<float>(Application::GetMilliseconds()) / 1000.0f) * 255.0f));
                
                SetColor(color);
            }
            
            Application::GetRenderer()->RenderTexture(Location, Scale, textTexture);
        }

        void SetSize(int newSize)
        {
            fontSize = newSize;
            RefreshTexture();
        }
        
        void SetText(const std::string& newText)
        {
            text = newText;
            RefreshTexture();
        }
        
        void SetColor(const Color& color)
        {
            textColor = color;
            RefreshTexture();
        }
        
        void SetLocation(Vector2D inLoc) { Location = inLoc; }

        void SetPulse(bool inVal) { bPulse = inVal; };
        
    private:

        void RefreshTexture()
        {
            if (textTexture)
                textTexture->Destroy();
            textTexture = new Texture(fontPath, fontSize, text, textColor);
            int w, h;
            SDL_QueryTexture(textTexture->GetSDLTexture(), nullptr, nullptr, &w, &h);
            Scale = Vector2D(w, h);
        }
        
        bool bPulse{false};
        
        std::string fontPath;
        int fontSize;
        std::string text;
        Color textColor;
        
        Vector2D Location{Vector2D(20, 20)};
        Vector2D Scale{Vector2D::Zero()};
        Texture* textTexture{nullptr};
    };
}
