#pragma once

#include <vector>

#include "Core.h"
#include "Window.h"

namespace DrEngine {
	
	class InputManager;
	struct CollisionData;
	
	namespace ECS
	{
		class Manager;
		class CollisionComponent;
	}

	class DRENGINE_API Application
	{
	public:
		Application(char* name = "App", int width = 800, int height = 600, bool fullscreen = false);
		virtual ~Application();

		void Run();

		virtual void BeginPlay();
		
		virtual void Update(float deltaTime);

		virtual void Draw(float deltaTime);
		
		static ECS::Manager* manager;
		
		/* Getters and Setters */
		Window* GetWindow() const { return window; }
		
		static ECS::Manager* GetManager() { return manager; };
		static InputManager* GetInputManager() { return inputManager; };
		static Uint32 GetMilliseconds() { return Milliseconds; };
		static SDL_Event& GetEvent() { return event; };
		static float GetDeltaTime() { return DeltaTime; };
		static Renderer* GetRenderer() { return renderer; };

		/* Collision Helper */
		static void AddCollisionComp(ECS::CollisionComponent* inComp);
	private:
		static InputManager* inputManager;
		static Uint32 Milliseconds;
		static SDL_Event event;
		static float DeltaTime;
		static Renderer* renderer;
		
		Window* window;

		char* AppName = "App";
	};

	// To be defined in client
	Application* CreateApplication();

}

