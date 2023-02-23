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

#include <iostream>



void load()
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

	//Other syntax
	//const auto textRenderer = textObj->AddComponent<dae::TextRenderer>(new dae::TextRenderer{ "Programming 4 Assignment", font});
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}