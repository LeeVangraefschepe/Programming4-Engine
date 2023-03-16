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

#include "Renderer.h"
#include "TrashCacheInt.h"


void Demo()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	const auto background = std::make_shared<dae::GameObject>();
	background->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("background.tga"));
	background->RemoveComponent<dae::Transform>();
	scene.Add(background);

	const auto logoObj = std::make_shared<dae::GameObject>();
	logoObj->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("logo.tga"));
	logoObj->GetComponent<dae::Transform>().lock()->SetPosition(216, 180);
	scene.Add(logoObj);

	const auto textObj = std::make_shared<dae::GameObject>();
	textObj->AddComponent<dae::TextRenderer>("Programming 4 Assignment", font);
	textObj->GetComponent<dae::Transform>().lock()->SetPosition(80, 20);
	scene.Add(textObj);

	const auto fpsObj = std::make_shared<dae::GameObject>();
	fpsObj->AddComponent<dae::FPS>();
	fpsObj->GetComponent<dae::Transform>().lock()->SetPosition(10, 10);
	scene.Add(fpsObj);


	///Rotate around
	const auto blancObj0 = std::make_shared<dae::GameObject>();
	blancObj0->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("RedTank.png"));
	blancObj0->AddComponent<dae::RotateAroundComponent>(glm::vec3{ 320 - 10,300,0 }, 20.f, 100.f);
	scene.Add(blancObj0);

	const auto blancObj1 = std::make_shared<dae::GameObject>();
	blancObj1->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("GreenTank.png"));
	blancObj1->SetParent(blancObj0, false);
	blancObj1->AddComponent<dae::RotateAroundComponent>(40.f, -200.f);
	scene.Add(blancObj1);
}

void TrashTheCache()
{
	auto& renderer = dae::Renderer::GetInstance();
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Trash the cache");
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	renderer.SetBackgroundColor(SDL_Color{ 61,90,110 });

	const auto test = std::make_shared<dae::GameObject>();
	test->AddComponent<dae::TrashCacheInt>();
	scene.Add(test);

	const auto textObj = std::make_shared<dae::GameObject>();
	textObj->AddComponent<dae::TextRenderer>("Programming 4 Assignment", font);
	textObj->GetComponent<dae::Transform>().lock()->SetPosition(80, 20);
	scene.Add(textObj);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/", 1280,720);
	engine.Run(TrashTheCache);
    return 0;
}