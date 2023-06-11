#include "GameOverScene.h"

#include "GameOverManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "SpriteRenderer.h"


void dae::GameOverScene::Load()
{
	auto& sceneManager = SceneManager::GetInstance();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//const auto screenWidth = static_cast<float>(sceneManager.GetWidth());
	//const auto screenHeight = static_cast<float>(sceneManager.GetHeight());

	sceneManager.SetActiveScene(new Scene{ "MainMenu" });
	const auto scene = sceneManager.GetActiveScene();

	const auto manager = new GameObject{};
	manager->AddComponent<GameOverManager>();
	scene->Add(manager);

	const auto background = new GameObject{};
	background->AddComponent<SpriteRenderer>(ResourceManager::GetInstance().LoadTexture("gameoverHD.png"));
	scene->Add(background);
}
