#pragma once

#include "TransformComponent.h"
#include "../Component.h"
#include "../Entity.h"

using namespace DrEngine;
using namespace DrEngine::ECS;

namespace DrEngine::ECS
{
    class DRENGINE_API CollisionComponent : public Component
    {
    public:
        void BeginPlay() override
        {
            transform = GetOwner()->GetComponentByClass<TransformComponent>();
            if (!transform)
            {
                DE_ERROR("Transform component not found for CollisionComp on Entity {0}", GetOwner()->GetName());
            }

            Application::AddCollisionComp(this);
        }

        void OnCollision(const CollisionData& inData)
        {
            for (const auto& f : callbacks)
            {
                f(inData);
            }
        }

        template <class T>
        void AddCallback(T* obj, void(T::* const inCallback)(const CollisionData&))
        {
            callbacks.push_back(std::bind(inCallback, obj, std::placeholders::_1));
        }
        
        TransformComponent* GetTransform() const { return transform; };

    private:
        TransformComponent* transform{nullptr};

        std::vector<std::function<void(const CollisionData&)>> callbacks;
    };
}