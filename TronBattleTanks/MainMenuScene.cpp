#include "MainMenuScene.h"

#include "AudioManager.h"
#include "GameModeManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "SpriteRenderer.h"
#include "TutorialComponent.h"

void dae::MainMenuScene::Load()
{
	auto& sceneManager = SceneManager::GetInstance();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//const auto screenWidth = static_cast<float>(sceneManager.GetWidth());
	//const auto screenHeight = static_cast<float>(sceneManager.GetHeight());

	ServiceLocator::GetAudioSystem()->Play(AudioManager::Music::MainMenu, 1.f);

	sceneManager.SetActiveScene(new Scene{ "MainMenu" });
	const auto scene = sceneManager.GetActiveScene();

	const auto tutorialComponent = new GameObject{};
	tutorialComponent->AddComponent<TutorialComponent>();
	scene->Add(tutorialComponent);

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
