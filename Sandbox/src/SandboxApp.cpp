#pragma warning (push)
#pragma warning (disable: 4251)
#include "DrEngine.h"
#pragma warning (pop)

#include "SDL.h"

#include "Components/FpsComp.h"
#include "Entities/Ball.h"
#include "Entities/Paddle.h"

using namespace DrEngine;
using namespace DrEngine::ECS;

class Sandbox : public DrEngine::Application
{
public:
	Sandbox() : DrEngine::Application("Pong made with DrEngine", 800, 600, false)
	{
	}

	~Sandbox()
	{
	}

	virtual void BeginPlay() override
	{
		Application::BeginPlay();

		const auto p1 = manager->AddEntity<Paddle>(Vector2D(14, 200), Color(0, 255, 0), "paddle1");
		paddles.push_back(p1);

		const auto p2 = manager->AddEntity<Paddle>(Vector2D(776, 200), Color(0, 0, 255), "paddle2");
		paddles.push_back(p2);

		BallRef = manager->AddEntity<Ball>(paddles, "Ball");

		FpsCounter = manager->AddEntity("FpsCounter");
		FpsCounter->AddComponent<FpsComp>();
		const auto fpsText = FpsCounter->AddComponent<TextComp>("Assets/Fonts/Sans.ttf", 18, "FPS: 30");
		fpsText->SetLocation(Vector2D(720, 10));
		fpsText->SetColor({255, 255, 255, 255});

		Desc = manager->AddEntity("Desc");
		const auto descText = Desc->AddComponent<TextComp>("Assets/Fonts/Sans.ttf", 14, "Made using DrEngine. Made by AvnishGameDev.");
		descText->SetLocation(Vector2D(460, 580));
		descText->SetPulse(true);

		bg = manager->AddEntity("bg");
		bg->SetBatch(Tile);
		bg->AddComponent<TransformComponent>()->Scale = Vector2D(800, 600);
		bg->AddComponent<RectComp>();
		bg->AddComponent<SpriteComponent>("Assets/Images/bg-updated.jpg");
		
		bgMusic = new Music("Assets/Audio/bg-music.mp3");
		if (bgMusic->IsValid())
		{
			bgMusic->PlayMusic(-1);	
		}
		
	}

	virtual void Update(float deltaTime) override
	{
		Application::Update(deltaTime);

		const int ballScore = BallRef->GetScore();
		if (currentScore != ballScore)
		{
			currentScore = ballScore;
			std::string text = "Score: " + std::to_string(currentScore);
			BallRef->GetComponentByClass<TextComp>()->SetText(text);
		}

		float fps = FpsCounter->GetComponentByClass<FpsComp>()->GetFPS();
		std::string fpsText = "FPS: " + std::to_string(static_cast<int>(fps));
		FpsCounter->GetComponentByClass<TextComp>()->SetText(fpsText);
		
		i++;
	}

	virtual void Draw(float deltaTime) override
	{
		Application::Draw(deltaTime);
		
	}

	std::vector<Entity*> paddles;
	Ball* BallRef;
	Entity* FpsCounter;
	Entity* Desc;
	Entity* bg;

	int currentScore{0};

	Music* bgMusic{nullptr};
	
	int i{0};
};

DrEngine::Application* DrEngine::CreateApplication()
{
	return new Sandbox();
}