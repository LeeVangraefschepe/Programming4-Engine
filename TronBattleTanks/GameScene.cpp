#include "GameScene.h"
#include "AudioManager.h"
#include "AudioSystemSDL2.h"
#include "CollisionComponent.h"
#include "Commands.h"
#include "FPS.h"
#include "GridComponent.h"
#include "HealthComponent.h"
#include "HealthDisplayComponent.h"
#include "InputManager.h"
#include "PlayerComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "ScoreComponent.h"
#include "ScoreDisplayComponent.h"
#include "ServiceLocator.h"
#include "TextRenderer.h"
#include "Transform.h"
#include "TutorialComponent.h"

#include <SDL_keycode.h>

#include "EnemyController.h"

void dae::GameScene::Load()
{
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	ServiceLocator::GetAudioSystem()->Play(AudioManager::Music::MainMenu, 0.1f);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	const auto screenWidth = static_cast<float>(sceneManager.GetWidth());
	const auto screenHeight = static_cast<float>(sceneManager.GetHeight());

	sceneManager.SetActiveScene(new Scene{ "GameScene" });
	const auto scene = sceneManager.GetActiveScene();

	const auto background = new GameObject{};
	background->AddComponent<SpriteRenderer>(ResourceManager::GetInstance().LoadTexture("backgroundHD.png"));
	scene->Add(background);

	const auto tutorialComponent = new GameObject{};
	tutorialComponent->AddComponent<TutorialComponent>();
	scene->Add(tutorialComponent);

	const auto logoObj = new GameObject();
	const auto logoImage = logoObj->AddComponent<SpriteRenderer>(ResourceManager::GetInstance().LoadTexture("logo.tga"));
	auto imageSize = logoImage->GetDimensions();
	logoObj->GetComponent<Transform>()->SetPosition(screenWidth / 2.f - imageSize.x / 2.f, screenHeight / 2.f - imageSize.y / 2.f);
	scene->Add(logoObj);

	const auto textObj = new GameObject();
	const auto textTitle = textObj->AddComponent<TextRenderer>("Programming 4 Assignment", font);
	imageSize = textTitle->GetDimensions();
	textObj->GetComponent<Transform>()->SetPosition(screenWidth / 2.f - imageSize.x / 2.f, 20);
	scene->Add(textObj);

	const auto fpsObj = new GameObject();
	fpsObj->AddComponent<FPS>();
	fpsObj->GetComponent<Transform>()->SetPosition(10, 10);
	scene->Add(fpsObj);

	const std::vector playerLayers{0, 1, 2};

	const auto player0 = new GameObject();
	const auto p0Health = player0->AddComponent<HealthComponent>(3.f);
	const auto p0Score = player0->AddComponent<ScoreComponent>();
	imageSize = player0->AddComponent<SpriteRenderer>(ResourceManager::GetInstance().LoadTexture("RedTank.png"))->GetDimensions();
	player0->GetComponent<Transform>()->SetLocalPosition(20.f, screenHeight / 2.f - imageSize.y / 2.f);
	player0->AddComponent<CollisionComponent>(playerLayers)->SetSize(imageSize.x, imageSize.y);
	const auto p0Component = player0->AddComponent<PlayerComponent>();
	scene->Add(player0);

	const auto p0HealthDisplay = new GameObject();
	p0HealthDisplay->GetComponent<Transform>()->SetLocalPosition(0, screenHeight - 250.f);
	p0HealthDisplay->AddComponent<HealthDisplayComponent>(p0Health);
	scene->Add(p0HealthDisplay);

	const auto p0ScoreDisplay = new GameObject();
	p0ScoreDisplay->GetComponent<Transform>()->SetLocalPosition(0, screenHeight - 200.f);
	p0ScoreDisplay->AddComponent<ScoreDisplayComponent>(p0Score);
	scene->Add(p0ScoreDisplay);

	const auto player1 = new GameObject();
	const auto p1Health = player1->AddComponent<HealthComponent>(10.f);
	const auto p1Score = player1->AddComponent<ScoreComponent>();
	imageSize = player1->AddComponent<SpriteRenderer>(ResourceManager::GetInstance().LoadTexture("GreenTank.png"))->GetDimensions();
	player1->GetComponent<Transform>()->SetLocalPosition(screenWidth - 50.f - imageSize.x, screenHeight / 2.f - imageSize.y / 2.f);
	player1->AddComponent<CollisionComponent>(playerLayers)->SetSize(imageSize.x, imageSize.y);
	const auto p1Component = player1->AddComponent<PlayerComponent>();
	scene->Add(player1);

	const auto p1HealthDisplay = new GameObject();
	p1HealthDisplay->GetComponent<Transform>()->SetLocalPosition(0, screenHeight - 100.f);
	p1HealthDisplay->AddComponent<HealthDisplayComponent>(p1Health);
	scene->Add(p1HealthDisplay);

	const auto p1ScoreDisplay = new GameObject();
	p1ScoreDisplay->GetComponent<Transform>()->SetLocalPosition(0, screenHeight - 50.f);
	p1ScoreDisplay->AddComponent<ScoreDisplayComponent>(p1Score);
	scene->Add(p1ScoreDisplay);

	const auto p0Move = new MoveCommand{ p0Component };
	const auto p1Move = new MoveCommand{ p1Component };
	input.BindCommand<MoveCommand>(p0Move, 0, Controller::ControllerButton::DPadLeft, Controller::ControllerButton::DPadUp, Controller::ControllerButton::DPadRight, Controller::ControllerButton::DPadDown, InputManager::InputType::Axis);
	input.BindCommand<MoveCommand>(p1Move, SDLK_q, SDLK_z, SDLK_d, SDLK_s, InputManager::InputType::Axis);

	const auto p0Fire = new FireCommand{ p0Component };
	input.BindCommand<FireCommand>(p0Fire, 0, Controller::ControllerButton::ButtonA, InputManager::InputType::OnButtonDown);
	const auto p1Fire = new FireCommand{ p1Component };
	input.BindCommand<FireCommand>(p1Fire, SDLK_SPACE, InputManager::InputType::OnButtonDown);

	const auto grid = new GameObject{};
	grid->AddComponent<GridComponent>(glm::vec2{ 12, 12 })->LoadGrid("Level/LevelLayout1.csv");
	scene->Add(grid);

	const auto enemy = new GameObject();
	imageSize = enemy->AddComponent<SpriteRenderer>(ResourceManager::GetInstance().LoadTexture("GreenTank.png"))->GetDimensions();
	enemy->GetComponent<Transform>()->SetLocalPosition(screenWidth - 50.f - imageSize.x, screenHeight / 2.f - imageSize.y / 2.f);
	enemy->AddComponent<HealthComponent>(1.f);
	enemy->AddComponent<CollisionComponent>(playerLayers)->SetSize(imageSize.x, imageSize.y);
	enemy->AddComponent<EnemyController>();
	scene->Add(enemy);
}
