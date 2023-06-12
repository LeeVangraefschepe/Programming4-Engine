#include "GameScene.h"

#include <iostream>

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

#include <SDL_keycode.h>

#include "EnemyController.h"
#include "GameModeManager.h"
#include "LevelComponent.h"
#include "LevelManager.h"
#include "GameOverScene.h"

void dae::GameScene::Load()
{
	int levelId{};
	if (ServiceLocator::GetGameState()->GetLevelId(levelId))
	{
		GameOverScene::Load();
		return;
	}

	auto& sceneManager = SceneManager::GetInstance();

	ServiceLocator::GetAudioSystem()->Play(AudioManager::Music::GameMenu, 1.f);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//const auto screenWidth = static_cast<float>(sceneManager.GetWidth());
	//const auto screenHeight = static_cast<float>(sceneManager.GetHeight());

	sceneManager.SetActiveScene(new Scene{ "GameScene" });
	const auto scene = sceneManager.GetActiveScene();

	const auto background = new GameObject{};
	background->AddComponent<SpriteRenderer>(ResourceManager::GetInstance().LoadTexture("backgroundHD.png"));
	scene->Add(background);

	std::vector<GameObject*> players{};
	switch (GameModeManager::GetGameMode())
	{
	case GameModeManager::singleplayer:
		LoadSinglePlayer(players);
		break;
	case GameModeManager::versus:
		LoadVersus(players);
		break;
	case GameModeManager::coop:
		LoadCoop(players);
		break;
	}

	const auto grid = new GameObject{};
	const auto level = grid->AddComponent<LevelComponent>();
	level->LoadLevel(levelId);

	std::vector<std::function<void(const glm::vec2& position)>> spawnPlayers{};
	spawnPlayers.reserve(players.size());
	for (auto& player : players)
	{
		spawnPlayers.emplace_back([&](const glm::vec2& position)
			{
				player->GetComponent<Transform>()->SetLocalPosition(position);
				player->GetComponent<HealthComponent>()->ResetHealth();
				scene->Add(player);
			});
	}
	level->SpawnPlayers(spawnPlayers);

	std::vector<GameObject*> enemies{};
	const std::vector enemyLayers{0, 1, 2};
	level->SpawnEnemies
	(
		[&](const glm::vec2& position)
		{
			const auto enemy = new GameObject();
			const auto imageSize = enemy->AddComponent<SpriteRenderer>(ResourceManager::GetInstance().LoadTexture("BlueTank.png"))->GetDimensions();
			enemy->GetComponent<Transform>()->SetLocalPosition(position);
			enemy->AddComponent<HealthComponent>(3.f);
			enemy->AddComponent<CollisionComponent>(enemyLayers)->SetSize(imageSize.x, imageSize.y);
			enemy->AddComponent<EnemyController>(30.f,100);
			scene->Add(enemy);
			enemies.emplace_back(enemy);
		},
		[&](const glm::vec2& position)
		{
			const auto enemy = new GameObject();
			const auto imageSize = enemy->AddComponent<SpriteRenderer>(ResourceManager::GetInstance().LoadTexture("Recognizer.png"))->GetDimensions();
			enemy->GetComponent<Transform>()->SetLocalPosition(position);
			enemy->AddComponent<HealthComponent>(3.f);
			enemy->AddComponent<CollisionComponent>(enemyLayers)->SetSize(imageSize.x, imageSize.y);
			enemy->AddComponent<EnemyController>(60.f,250);
			scene->Add(enemy);
			enemies.emplace_back(enemy);
		}
	);

	grid->AddComponent<LevelManager>(level, players, enemies);
	scene->Add(grid);

	const auto fpsObj = new GameObject();
	fpsObj->AddComponent<FPS>();
	fpsObj->GetComponent<Transform>()->SetPosition(10, 10);
	scene->Add(fpsObj);
}

void dae::GameScene::LoadSinglePlayer(std::vector<GameObject*>& players)
{
	auto& input = InputManager::GetInstance();
	const auto scene = SceneManager::GetInstance().GetActiveScene();
	const std::vector playerLayers{0, 1, 2};
	const auto screenHeight = static_cast<float>(SceneManager::GetInstance().GetHeight());

	const auto player1 = new GameObject();
	const auto p1Health = player1->AddComponent<HealthComponent>(3.f);
	const auto p1Score = player1->AddComponent<ScoreComponent>();
	const auto imageSize = player1->AddComponent<SpriteRenderer>(ResourceManager::GetInstance().LoadTexture("GreenTank.png"))->GetDimensions();
	player1->AddComponent<CollisionComponent>(playerLayers)->SetSize(imageSize.x, imageSize.y);
	const auto p1Component = player1->AddComponent<PlayerComponent>();
	players.push_back(player1);

	const auto p1HealthDisplay = new GameObject();
	p1HealthDisplay->GetComponent<Transform>()->SetLocalPosition(300, screenHeight - 20.f);
	p1HealthDisplay->AddComponent<HealthDisplayComponent>(p1Health);
	scene->Add(p1HealthDisplay);

	const auto p1ScoreDisplay = new GameObject();
	p1ScoreDisplay->GetComponent<Transform>()->SetLocalPosition(0, screenHeight - 20.f);
	p1ScoreDisplay->AddComponent<ScoreDisplayComponent>(p1Score);
	scene->Add(p1ScoreDisplay);

	const auto p1Move = new MoveCommand{ p1Component };
	const auto p11Move = new MoveCommand{ p1Component };
	input.BindCommand<MoveCommand>(p1Move, SDLK_q, SDLK_z, SDLK_d, SDLK_s, InputManager::InputType::Axis);
	input.BindCommand<MoveCommand>(p11Move, 0, Controller::ControllerButton::DPadLeft, Controller::ControllerButton::DPadUp, Controller::ControllerButton::DPadRight, Controller::ControllerButton::DPadDown, InputManager::InputType::Axis);

	const auto p1Fire = new FireCommand{ p1Component };
	const auto p11Fire = new FireCommand{ p1Component };
	input.BindCommand<FireCommand>(p1Fire, SDLK_SPACE, InputManager::InputType::OnButtonDown);
	input.BindCommand<FireCommand>(p11Fire, 0, Controller::ControllerButton::ButtonA, InputManager::InputType::OnButtonDown);
}

void dae::GameScene::LoadVersus(std::vector<GameObject*>& players)
{
	LoadCoop(players);
}

void dae::GameScene::LoadCoop(std::vector<GameObject*>& players)
{
	auto& input = InputManager::GetInstance();
	const auto scene = SceneManager::GetInstance().GetActiveScene();
	const std::vector playerLayers{0, 1, 2};
	const auto screenHeight = static_cast<float>(SceneManager::GetInstance().GetHeight());

	const auto player0 = new GameObject();
	const auto p0Health = player0->AddComponent<HealthComponent>(3.f);
	const auto p0Score = player0->AddComponent<ScoreComponent>();
	auto imageSize = player0->AddComponent<SpriteRenderer>(ResourceManager::GetInstance().LoadTexture("RedTank.png"))->GetDimensions();
	player0->AddComponent<CollisionComponent>(playerLayers)->SetSize(imageSize.x, imageSize.y);
	const auto p0Component = player0->AddComponent<PlayerComponent>();
	players.push_back(player0);

	const auto p0HealthDisplay = new GameObject();
	p0HealthDisplay->GetComponent<Transform>()->SetLocalPosition(300, screenHeight - 60.f);
	p0HealthDisplay->AddComponent<HealthDisplayComponent>(p0Health);
	scene->Add(p0HealthDisplay);

	const auto p0ScoreDisplay = new GameObject();
	p0ScoreDisplay->GetComponent<Transform>()->SetLocalPosition(0, screenHeight - 60.f);
	p0ScoreDisplay->AddComponent<ScoreDisplayComponent>(p0Score);
	scene->Add(p0ScoreDisplay);

	const auto player1 = new GameObject();
	const auto p1Health = player1->AddComponent<HealthComponent>(3.f);
	const auto p1Score = player1->AddComponent<ScoreComponent>();
	imageSize = player1->AddComponent<SpriteRenderer>(ResourceManager::GetInstance().LoadTexture("GreenTank.png"))->GetDimensions();
	player1->AddComponent<CollisionComponent>(playerLayers)->SetSize(imageSize.x, imageSize.y);
	const auto p1Component = player1->AddComponent<PlayerComponent>();
	players.push_back(player1);

	const auto p1HealthDisplay = new GameObject();
	p1HealthDisplay->GetComponent<Transform>()->SetLocalPosition(300, screenHeight - 20.f);
	p1HealthDisplay->AddComponent<HealthDisplayComponent>(p1Health);
	scene->Add(p1HealthDisplay);

	const auto p1ScoreDisplay = new GameObject();
	p1ScoreDisplay->GetComponent<Transform>()->SetLocalPosition(0, screenHeight - 20.f);
	p1ScoreDisplay->AddComponent<ScoreDisplayComponent>(p1Score);
	scene->Add(p1ScoreDisplay);

	const auto p0Move = new MoveCommand{ p0Component };
	const auto p1Move = new MoveCommand{ p1Component };
	const auto p11Move = new MoveCommand{ p1Component };
	input.BindCommand<MoveCommand>(p0Move, 0, Controller::ControllerButton::DPadLeft, Controller::ControllerButton::DPadUp, Controller::ControllerButton::DPadRight, Controller::ControllerButton::DPadDown, InputManager::InputType::Axis);
	input.BindCommand<MoveCommand>(p1Move, SDLK_q, SDLK_z, SDLK_d, SDLK_s, InputManager::InputType::Axis);
	input.BindCommand<MoveCommand>(p11Move, 1, Controller::ControllerButton::DPadLeft, Controller::ControllerButton::DPadUp, Controller::ControllerButton::DPadRight, Controller::ControllerButton::DPadDown, InputManager::InputType::Axis);

	const auto p0Fire = new FireCommand{ p0Component };
	input.BindCommand<FireCommand>(p0Fire, 0, Controller::ControllerButton::ButtonA, InputManager::InputType::OnButtonDown);
	const auto p1Fire = new FireCommand{ p1Component };
	const auto p11Fire = new FireCommand{ p1Component };
	input.BindCommand<FireCommand>(p1Fire, SDLK_SPACE, InputManager::InputType::OnButtonDown);
	input.BindCommand<FireCommand>(p11Fire, 1, Controller::ControllerButton::ButtonA, InputManager::InputType::OnButtonDown);
}
