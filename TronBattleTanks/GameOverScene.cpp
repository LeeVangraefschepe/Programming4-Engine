#include "GameOverScene.h"

#include <iostream>

#include "GameOverManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "ScoreManager.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"


void dae::GameOverScene::Load()
{
	auto& sceneManager = SceneManager::GetInstance();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	const auto screenWidth = static_cast<float>(sceneManager.GetWidth());
	//const auto screenHeight = static_cast<float>(sceneManager.GetHeight());

	sceneManager.SetActiveScene(new Scene{ "GameOver" });
	const auto scene = sceneManager.GetActiveScene();

	const auto background = new GameObject{};
	background->AddComponent<SpriteRenderer>(ResourceManager::GetInstance().LoadTexture("gameoverHD.png"));
	scene->Add(background);

	std::cout << "Submit highscore: " << ScoreManager::GetInstance().GetScore() << "\n";
	ScoreManager::GetInstance().SubmitScore("LEE");

	const auto scores = ScoreManager::GetInstance().GetScores();
	for (int i{}; i < static_cast<int>(scores.size()); ++i)
	{
		const auto textObj = new GameObject();
		const auto textTitle = textObj->AddComponent<TextRenderer>(scores[i], font);
		const auto imageSize = textTitle->GetDimensions();
		textObj->GetComponent<Transform>()->SetPosition(screenWidth / 2.f - imageSize.x / 2.f, static_cast<float>(250 + i * 30));
		scene->Add(textObj);
	}

	const auto manager = new GameObject{};
	manager->AddComponent<GameOverManager>();
	scene->Add(manager);

	
}
