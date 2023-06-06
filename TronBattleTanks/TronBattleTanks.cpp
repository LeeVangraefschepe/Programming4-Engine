#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "FPS.h"
#include "TextRenderer.h"
#include "Scene.h"
#include "RotateAroundComponent.h"
#include "HealthComponent.h"

#include <iostream>

#include "AudioManager.h"
#include "Commands.h"
#include "InputManager.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "ScoreComponent.h"
#include "HealthDisplayComponent.h"
#include "ScoreDisplayComponent.h"
#include "ServiceLocator.h"
#include "TutorialComponent.h"
#include "AudioSystemSDL2.h"
#include "GridComponent.h"

void Demo()
{
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto& input = dae::InputManager::GetInstance();

	dae::AudioManager::GetInstance().SetService(std::make_unique<dae::AudioSystemSDL2>());
	dae::ServiceLocator::GetAudioSystem()->Play(dae::AudioManager::Music::MainMenu, 0.1f);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	const float screenWidth = static_cast<float>(sceneManager.GetWidth());
	const float screenHeight = static_cast<float>(sceneManager.GetHeight());

	sceneManager.SetActiveScene(new dae::Scene{ "Demo" });
	auto scene = sceneManager.GetActiveScene();

	const auto background = new dae::GameObject{};
	background->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("backgroundHD.png"));
	scene->Add(background);

	const auto tutorialComponent = new dae::GameObject{};
	tutorialComponent->AddComponent<dae::TutorialComponent>();
	scene->Add(tutorialComponent);

	const auto logoObj = new dae::GameObject();
	const auto logoImage = logoObj->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("logo.tga"));
	auto imageSize = logoImage->GetDimensions();
	logoObj->GetComponent<dae::Transform>()->SetPosition(screenWidth / 2.f - imageSize.x / 2.f, screenHeight / 2.f - imageSize.y / 2.f);
	scene->Add(logoObj);

	const auto textObj = new dae::GameObject();
	const auto textTitle = textObj->AddComponent<dae::TextRenderer>("Programming 4 Assignment", font);
	imageSize = textTitle->GetDimensions();
	textObj->GetComponent<dae::Transform>()->SetPosition(screenWidth / 2.f - imageSize.x / 2.f, 20);
	scene->Add(textObj);

	const auto grid = new dae::GameObject{};
	grid->AddComponent<dae::GridComponent>(glm::vec2{ 12,12 })->LoadGrid("Level/LevelLayout1.csv");
	scene->Add(grid);

	const auto fpsObj = new dae::GameObject();
	fpsObj->AddComponent<dae::FPS>();
	fpsObj->GetComponent<dae::Transform>()->SetPosition(10, 10);
	scene->Add(fpsObj);

	const auto player0 = new dae::GameObject();
	const auto p0Health = player0->AddComponent<dae::HealthComponent>(3.f);
	const auto p0Score = player0->AddComponent<dae::ScoreComponent>();
	imageSize = player0->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("RedTank.png"))->GetDimensions();
	player0->GetComponent<dae::Transform>()->SetLocalPosition(20.f, screenHeight / 2.f - imageSize.y / 2.f);
	player0->AddComponent<dae::CollisionComponent>()->SetSize(imageSize.x, imageSize.y);
	const auto p0Component = player0->AddComponent<dae::PlayerComponent>();
	scene->Add(player0);

	const auto p0HealthDisplay = new dae::GameObject();
	p0HealthDisplay->GetComponent<dae::Transform>()->SetLocalPosition(0, screenHeight - 250.f);
	p0HealthDisplay->AddComponent<dae::HealthDisplayComponent>(p0Health);
	scene->Add(p0HealthDisplay);

	const auto p0ScoreDisplay = new dae::GameObject();
	p0ScoreDisplay->GetComponent<dae::Transform>()->SetLocalPosition(0, screenHeight - 200.f);
	p0ScoreDisplay->AddComponent<dae::ScoreDisplayComponent>(p0Score);
	scene->Add(p0ScoreDisplay);

	const auto player1 = new dae::GameObject();
	const auto p1Health = player1->AddComponent<dae::HealthComponent>(10.f);
	const auto p1Score = player1->AddComponent<dae::ScoreComponent>();
	imageSize = player1->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("GreenTank.png"))->GetDimensions();
	player1->GetComponent<dae::Transform>()->SetLocalPosition(screenWidth - 50.f - imageSize.x, screenHeight / 2.f - imageSize.y / 2.f);
	player1->AddComponent<dae::CollisionComponent>()->SetSize(imageSize.x, imageSize.y);
	const auto p1Component = player1->AddComponent<dae::PlayerComponent>();
	scene->Add(player1);

	const auto p1HealthDisplay = new dae::GameObject();
	p1HealthDisplay->GetComponent<dae::Transform>()->SetLocalPosition(0, screenHeight - 100.f);
	p1HealthDisplay->AddComponent<dae::HealthDisplayComponent>(p1Health);
	scene->Add(p1HealthDisplay);

	const auto p1ScoreDisplay = new dae::GameObject();
	p1ScoreDisplay->GetComponent<dae::Transform>()->SetLocalPosition(0, screenHeight - 50.f);
	p1ScoreDisplay->AddComponent<dae::ScoreDisplayComponent>(p1Score);
	scene->Add(p1ScoreDisplay);

	const auto p0Move = new dae::MoveCommand{ p0Component };
	const auto p1Move = new dae::MoveCommand{ p1Component };
	input.BindCommand<dae::MoveCommand>(p0Move, 0, dae::Controller::ControllerButton::DPadLeft, dae::Controller::ControllerButton::DPadUp, dae::Controller::ControllerButton::DPadRight, dae::Controller::ControllerButton::DPadDown, dae::InputManager::InputType::Axis);
	input.BindCommand<dae::MoveCommand>(p1Move, SDLK_a, SDLK_w, SDLK_d, SDLK_s, dae::InputManager::InputType::Axis);

	const auto p0Fire = new dae::FireCommand{ p0Component };
	input.BindCommand<dae::FireCommand>(p0Fire, 0, dae::Controller::ControllerButton::ButtonA, dae::InputManager::InputType::OnButtonDown);
	const auto p1Fire = new dae::FireCommand{ p1Component };
	input.BindCommand<dae::FireCommand>(p1Fire, SDLK_SPACE, dae::InputManager::InputType::OnButtonDown);
}

int main(int, char* [])
{
    dae::Minigin engine("../Data/", 700, 720);
    engine.Run(Demo);
    return 0;
}
