#pragma once

#include "../Core.h"

namespace DrEngine
{
    class DRENGINE_API Vector2D
    {
    public:
        Vector2D()
        {
            x = 0;
            y = 0;
        }

        Vector2D(float n)
        {
            x = n;
            y = n;
        }

        Vector2D(int inX, int inY)
        {
            x = static_cast<float>(inX);
            y = static_cast<float>(inY);
        }
        
        Vector2D(float inX, float inY)
        {
            x = inX;
            y = inY;
        }

        void Translate(const Vector2D& inVec) { SetX(X() + inVec.X()); SetY(Y() + inVec.Y()); };
        void TranslateX(float inVal) { SetX(X() + inVal); };
        void TranslateY(float inVal) { SetY(Y() + inVal); };
        
        float X() const { return x; }
        float Y() const { return y; }
        void SetX(float inVal) { x = inVal; }
        void SetY(float inVal) { y = inVal; }

        static Vector2D Zero() { return Vector2D(); };

        bool operator == (const Vector2D& vec2) const
        {
            return this->X() == vec2.X() && this->Y() == vec2.Y();
        }
        
        Vector2D operator + (const Vector2D& vec2) const
        {
            Vector2D finalVec;
            finalVec.SetX(this->X() + vec2.X());
            finalVec.SetY(this->Y() + vec2.Y());
            return finalVec;
        }

        Vector2D operator - (const Vector2D& vec2) const
        {
            Vector2D finalVec;
            finalVec.SetX(this->X() - vec2.X());
            finalVec.SetY(this->Y() - vec2.Y());
            return finalVec;
        }

        Vector2D operator += (const Vector2D& vec2)
        {
            this->SetX(this->X() + vec2.X());
            this->SetY(this->Y() + vec2.Y());
            return *this;
        }

        Vector2D operator -= (const Vector2D& vec2)
        {
            this->SetX(this->X() - vec2.X());
            this->SetY(this->Y() - vec2.Y());
            return *this;
        }

        Vector2D operator *= (const float n)
        {
            this->SetX(this->X() * n);
            this->SetY(this->Y() * n);
            return *this;
        }

        Vector2D operator * (const float n)
        {
            Vector2D finalVec;
            finalVec.SetX(this->X() * n);
            finalVec.SetY(this->Y() * n);
            return finalVec;
        }
        
    private:
        float x{0};
        float y{0};
    };
}
