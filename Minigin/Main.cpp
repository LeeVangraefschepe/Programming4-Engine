#include <SDL.h>
#include <steam_api.h>

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

#include "Commands.h"
#include "InputManager.h"
#include "Renderer.h"
#include "TrashCacheGameObject.h"
#include "TrashCacheInt.h"
#include "BasicAchievements.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "ScoreComponent.h"


void Demo()
{
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto& input = dae::InputManager::GetInstance();
	auto& achievements = dae::BasicAchievements::GetInstance();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	const float screenWidth = static_cast<float>(sceneManager.GetWidth());
	const float screenHeight = static_cast<float>(sceneManager.GetHeight());

	sceneManager.SetActiveScene(new dae::Scene{"Demo"});
	auto scene = sceneManager.GetActiveScene();

	achievements.ClearAchievements();

	const auto background = new dae::GameObject{};
	background->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("backgroundHD.png"));
	scene->Add(background);

	const auto logoObj = new dae::GameObject();
	const auto logoImage = logoObj->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("logo.tga"));
	auto imageSize = logoImage->GetDimensions();
	logoObj->GetComponent<dae::Transform>()->SetPosition(screenWidth/2.f - imageSize.x / 2.f, screenHeight / 2.f - imageSize.y / 2.f);
	scene->Add(logoObj);

	const auto textObj = new dae::GameObject();
	const auto textTitle = textObj->AddComponent<dae::TextRenderer>("Programming 4 Assignment", font);
	imageSize = textTitle->GetDimensions();
	textObj->GetComponent<dae::Transform>()->SetPosition(screenWidth / 2.f - imageSize.x / 2.f, 20);
	scene->Add(textObj);

	const auto fpsObj = new dae::GameObject();
	fpsObj->AddComponent<dae::FPS>();
	fpsObj->GetComponent<dae::Transform>()->SetPosition(10, 10);
	scene->Add(fpsObj);


	const auto player0 = new dae::GameObject();
	player0->AddComponent<dae::HealthComponent>(3.f);
	player0->AddComponent<dae::ScoreComponent>();
	imageSize = player0->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("RedTank.png"))->GetDimensions();
	player0->GetComponent<dae::Transform>()->SetLocalPosition(50.f, screenHeight / 2.f - imageSize.y / 2.f);
	player0->AddComponent<dae::CollisionComponent>()->SetSize(imageSize.x, imageSize.y);
	const auto p0Component = player0->AddComponent<dae::PlayerComponent>();
	scene->Add(player0);

	const auto player1 = new dae::GameObject();
	player1->AddComponent<dae::HealthComponent>(3.f);
	player1->AddComponent<dae::ScoreComponent>();
	imageSize = player1->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("GreenTank.png"))->GetDimensions();
	player1->GetComponent<dae::Transform>()->SetLocalPosition(screenWidth - 50.f - imageSize.x, screenHeight / 2.f - imageSize.y / 2.f);
	player1->AddComponent<dae::CollisionComponent>()->SetSize(imageSize.x, imageSize.y);
	const auto p1Component = player1->AddComponent<dae::PlayerComponent>();
	scene->Add(player1);

	const auto p0Move = new dae::MoveCommand{ p0Component };
	const auto p1Move = new dae::MoveCommand{ p1Component };
	input.BindCommand<dae::MoveCommand>(p0Move, 0, dae::Controller::ControllerButton::DPadLeft, dae::Controller::ControllerButton::DPadUp, dae::Controller::ControllerButton::DPadRight, dae::Controller::ControllerButton::DPadDown, dae::InputManager::InputType::Axis);
	input.BindCommand<dae::MoveCommand>(p1Move,SDLK_a, SDLK_w, SDLK_d, SDLK_s, dae::InputManager::InputType::Axis);

	const auto p0Fire = new dae::FireCommand{ p0Component };
	input.BindCommand<dae::FireCommand>(p0Fire, 0, dae::Controller::ControllerButton::ButtonA, dae::InputManager::InputType::OnButtonDown);

	p0Component->AddObservableObject(&achievements);
	p1Component->AddObservableObject(&achievements);
}

int main(int, char*[])
{
	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}

	dae::Minigin engine("../Data/", 1280,720);
	engine.Run(Demo);

	SteamAPI_Shutdown();
    return 0;
}