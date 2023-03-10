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


	///Rotate around
	const auto blancObj0 = std::make_shared<dae::GameObject>();
	blancObj0->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("RedTank.png"));
	blancObj0->AddComponent<dae::RotateAroundComponent>(glm::vec3{ 320-10,300,0 },20.f, 100.f);
	scene.Add(blancObj0);

	const auto blancObj1 = std::make_shared<dae::GameObject>();
	blancObj1->AddComponent<dae::SpriteRenderer>(dae::ResourceManager::GetInstance().LoadTexture("GreenTank.png"));
	blancObj1->SetParent(blancObj0, false);
	blancObj1->AddComponent<dae::RotateAroundComponent>(40.f, -200.f);
	scene.Add(blancObj1);

	//const auto emptyObj = std::make_shared<dae::GameObject>();
	//emptyObj->SetParent(blancObj1, false);
	//scene.Add(emptyObj);
	//
	//blancObj0->SetParent(emptyObj, false);

	/*
	///Limit test parenting
	//Create object2
	const auto transfrormObj2 = std::make_shared<dae::GameObject>();
	scene.Add(transfrormObj2);

	//Print world pos object2
	auto pos = transfrormObj2->GetComponent<dae::Transform>().lock()->GetWorldPosition();
	std::cout << pos.x << " " << pos.y << " " << pos.z << "\n";

	{
		//Create object(1) and set position to 10,10
		const auto transfrormObj = std::make_shared<dae::GameObject>();
		transfrormObj->GetComponent<dae::Transform>().lock()->SetLocalPosition(10, 10);

		//Set parent
		transfrormObj2->SetParent(transfrormObj, false);

		//Print world pos object2
		pos = transfrormObj2->GetComponent<dae::Transform>().lock()->GetWorldPosition();
		std::cout << pos.x << " " << pos.y << " " << pos.z << "\n";

		//Print local pos object2
		pos = transfrormObj2->GetComponent<dae::Transform>().lock()->GetLocalPosition();
		std::cout << pos.x << " " << pos.y << " " << pos.z << "\n";

		//Set parent transform on other location
		transfrormObj->GetComponent<dae::Transform>().lock()->SetLocalPosition(50, 50);

		//Print world pos object2
		pos = transfrormObj2->GetComponent<dae::Transform>().lock()->GetWorldPosition();
		std::cout << pos.x << " " << pos.y << " " << pos.z << "\n";
	}
	//Parent out of scope -> Deleted

	//Force update to check if world position stayed the same
	transfrormObj2->GetComponent<dae::Transform>().lock()->SetPositionDirty();

	//Get world location
	pos = transfrormObj2->GetComponent<dae::Transform>().lock()->GetWorldPosition();
	std::cout << pos.x << " " << pos.y << " " << pos.z << "\n";
	*/
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}