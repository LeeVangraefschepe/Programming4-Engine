#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "GameObject.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "FPS.h"
#include "TextRenderer.h"
#include "Scene.h"
#include "RotateAroundComponent.h"

#include <iostream>

#include "Commands.h"
#include "InputManager.h"
#include "Renderer.h"
#include "TrashCacheGameObject.h"
#include "TrashCacheInt.h"


void Demo()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& input = dae::InputManager::GetInstance();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	const auto background = std::make_shared<dae::GameObject>();
	//background->RemoveComponent<dae::Transform>();
	background->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("background.tga"));
	scene.Add(background);

	const auto logoObj = std::make_shared<dae::GameObject>();
	logoObj->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("logo.tga"));
	logoObj->GetComponent<dae::Transform>()->SetPosition(216, 180);
	scene.Add(logoObj);

	const auto textObj = std::make_shared<dae::GameObject>();
	textObj->AddComponent<dae::TextRenderer>("Programming 4 Assignment", font);
	textObj->GetComponent<dae::Transform>()->SetPosition(80, 20);
	scene.Add(textObj);

	const auto fpsObj = std::make_shared<dae::GameObject>();
	fpsObj->AddComponent<dae::FPS>();
	fpsObj->GetComponent<dae::Transform>()->SetPosition(10, 10);
	scene.Add(fpsObj);

	const auto player0 = std::make_shared<dae::GameObject>();
	player0->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("RedTank.png"));
	scene.Add(player0);

	const auto player1 = std::make_shared<dae::GameObject>();
	player1->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("RedTank.png"));
	scene.Add(player1);

	const auto p0Move = input.BindCommand<dae::MoveCommand>(0, dae::Controller::ControllerButton::LeftThumb, dae::InputManager::InputType::Axis, player0.get());
	const auto p1Move = input.BindCommand<dae::MoveCommand>(SDLK_q, SDLK_z, SDLK_d, SDLK_s, dae::InputManager::InputType::Axis, player1.get());
	p0Move->SetSpeed(50.f);
	p1Move->SetSpeed(100.f);

	const auto blancObj1 = std::make_shared<dae::GameObject>();
	blancObj1->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("GreenTank.png"));
	blancObj1->SetParent(player0, false);
	blancObj1->AddComponent<dae::RotateAroundComponent>(40.f, -200.f);
	scene.Add(blancObj1);
}

void TrashTheCache()
{
	auto& renderer = dae::Renderer::GetInstance();
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Trash the cache");
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	renderer.SetBackgroundColor(SDL_Color{ 61,90,110 });

	const auto ex02 = std::make_shared<dae::GameObject>();
	ex02->AddComponent<dae::TrashCacheInt>();
	scene.Add(ex02);

	const auto ex03 = std::make_shared<dae::GameObject>();
	ex03->AddComponent<dae::TrashCacheGameObject>();
	scene.Add(ex03);

	const auto textObj = std::make_shared<dae::GameObject>();
	textObj->AddComponent<dae::TextRenderer>("Programming 4 Assignment", font);
	textObj->GetComponent<dae::Transform>()->SetPosition(80, 20);
	scene.Add(textObj);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/", 1280,720);
	engine.Run(Demo);
    return 0;
}