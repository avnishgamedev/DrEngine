#pragma warning (push)
#pragma warning (disable: 4251)
#include "DrEngine.h"
#pragma warning (pop)

#include "SDL.h"

using namespace DrEngine;
using namespace DrEngine::ECS;

class Sandbox : public DrEngine::Application
{
public:
	Sandbox() : DrEngine::Application("Sandbox", 800, 600, false)
	{
	}

	~Sandbox()
	{
	}

	virtual void BeginPlay() override
	{
		Application::BeginPlay();
		
	}

	virtual void Update(float deltaTime) override
	{
		Application::Update(deltaTime);
	}

	virtual void Draw(float deltaTime) override
	{
		Application::Draw(deltaTime);
		
	}
};

DrEngine::Application* DrEngine::CreateApplication()
{
	return new Sandbox();
}