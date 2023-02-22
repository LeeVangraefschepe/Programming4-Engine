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
#include "Scene.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	const auto background = std::make_shared<dae::GameObject>();
	background->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("background.tga"));
	scene.Add(background);

	const auto logoObj = std::make_shared<dae::GameObject>();
	const auto spriteRenderer = logoObj->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("logo.tga"));
	spriteRenderer->SetPosition(216, 180);
	logoObj->GetComponent<dae::Transform>()->SetPosition(216, 180, 0);
	scene.Add(logoObj);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	const auto textObj = std::make_shared<dae::GameObject>();
	textObj->AddComponent<dae::TextRenderer>("Programming 4 Assignment", font);
	//const auto textRenderer = textObj->AddComponent<dae::TextRenderer>(new dae::TextRenderer{ "Programming 4 Assignment", font});
	//textRenderer->SetPosition(80, 20);
	textObj->GetComponent<dae::TextRenderer>()->SetPosition(80, 20);
	scene.Add(textObj);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}