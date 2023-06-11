#include "MainMenuScene.h"

#include "GameModeManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "SpriteRenderer.h"

void dae::MainMenuScene::Load()
{
	auto& sceneManager = SceneManager::GetInstance();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//const auto screenWidth = static_cast<float>(sceneManager.GetWidth());
	//const auto screenHeight = static_cast<float>(sceneManager.GetHeight());

	sceneManager.SetActiveScene(new Scene{ "MainMenu" });
	const auto scene = sceneManager.GetActiveScene();

	const auto background = new GameObject{};
	background->AddComponent<SpriteRenderer>(ResourceManager::GetInstance().LoadTexture("mainmenuHD.png"));
	scene->Add(background);

	std::vector<glm::vec2> positions
	{
		{80.f, 335.f},
		{80.f, 380.f},
		{80.f, 430.f}
	};
	const auto gameModeManager = new GameObject{};
	gameModeManager->AddComponent<GameModeManager>(positions);
	scene->Add(gameModeManager);
}
