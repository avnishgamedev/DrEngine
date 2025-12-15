#pragma once

#include "../ECS.h"

namespace DrEngine::ECS
{
    class DRENGINE_API CircleComp : public Component
    {
    public:
        CircleComp()
        {
        
        }
        ~CircleComp()
        {
        
        }

        void BeginPlay() override
        {
            transform = GetOwner()->GetComponentByClass<TransformComponent>();
            if (!transform)
            {
                DE_ERROR("Transform component not found for CircleComp on Entity {0}", GetOwner()->GetName());
            }
        }
    
        void Draw(float deltaTime) override
        {
            int X, Y;
            X = static_cast<int>(transform->GetLocation().X());
            Y = static_cast<int>(transform->GetLocation().Y());
        
            DrawCircle(X, Y, static_cast<int32_t>(transform->GetScale().X()));
        }
    
    private:

        TransformComponent* transform;
    
        void DrawCircle(int32_t centreX, int32_t centreY, int32_t radius)
        {
            const int32_t diameter = (radius * 2);

            int32_t x = (radius - 1);
            int32_t y = 0;
            int32_t tx = 1;
            int32_t ty = 1;
            int32_t error = (tx - diameter);

            while (x >= y)
            {
                //  Each of the following renders an octant of the circle
                Application::GetRenderer()->RenderPoint(Vector2D(centreX + x, centreY - y));
                Application::GetRenderer()->RenderPoint(Vector2D(centreX + x, centreY + y));
                Application::GetRenderer()->RenderPoint(Vector2D(centreX - x, centreY - y));
                Application::GetRenderer()->RenderPoint(Vector2D(centreX - x, centreY + y));
                Application::GetRenderer()->RenderPoint(Vector2D(centreX + y, centreY - x));
                Application::GetRenderer()->RenderPoint(Vector2D(centreX + y, centreY + x));
                Application::GetRenderer()->RenderPoint(Vector2D(centreX - y, centreY - x));
                Application::GetRenderer()->RenderPoint(Vector2D(centreX - y, centreY + x));

                if (error <= 0)
                {
                    ++y;
                    error += ty;
                    ty += 2;
                }

                if (error > 0)
                {
                    --x;
                    tx += 2;
                    error += (tx - diameter);
                }
            }
        }
    };
}