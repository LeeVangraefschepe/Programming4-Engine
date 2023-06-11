#include "GameOverManager.h"

#include <SDL_keycode.h>
#include <sstream>

#include "Commands.h"
#include "GameObject.h"
#include "InputManager.h"
#include "MainMenuScene.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "ScoreManager.h"
#include "TextRenderer.h"

dae::GameOverManager::GameOverManager(GameObject* pGameObject) : BaseComponent(pGameObject)
{
	auto& input = InputManager::GetInstance();
	const auto& sceneManager = SceneManager::GetInstance();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	const auto screenWidth = static_cast<float>(sceneManager.GetWidth());

	for (int i{}; i < m_tagSize; ++i)
	{
		m_tag[i] = 'A';
		const auto textObj = new GameObject();
		std::stringstream ss{};
		ss << m_tag[i];
		const auto textTitle = textObj->AddComponent<TextRenderer>(ss.str(), font);
		const auto imageSize = textTitle->GetDimensions();
		textObj->GetComponent<Transform>()->SetPosition(screenWidth / 2.f - imageSize.x / 2.f + (20.f * (i-1)), static_cast<float>(240));
		textObj->SetParent(pGameObject, false);
		m_text[i] = textTitle;
	}

	//Confirm
	const auto confirm = [this]()
	{
		Next();
	};
	auto keyboardCommand = new LambdaCommand{ confirm };
	auto controllerCommand = new LambdaCommand{ confirm };
	input.BindCommand<LambdaCommand>(keyboardCommand, SDLK_a, InputManager::InputType::OnButtonDown);
	input.BindCommand<LambdaCommand>(controllerCommand, 0, Controller::ControllerButton::ButtonA, InputManager::InputType::OnButtonDown);
	m_pCommands.push_back(keyboardCommand);
	m_pCommands.push_back(controllerCommand);

	//Up
	const auto up = [this]()
	{
		if (m_step < m_tagSize)
		{
			m_tag[m_step]++;
			std::stringstream ss{};
			ss << m_tag[m_step];
			m_text[m_step]->SetText(ss.str());
		}
	};
	keyboardCommand = new LambdaCommand{ up };
	controllerCommand = new LambdaCommand{ up };
	input.BindCommand<LambdaCommand>(keyboardCommand, SDLK_UP, InputManager::InputType::OnButtonDown);
	input.BindCommand<LambdaCommand>(controllerCommand, 0, Controller::ControllerButton::DPadUp, InputManager::InputType::OnButtonDown);
	m_pCommands.push_back(keyboardCommand);
	m_pCommands.push_back(controllerCommand);

	//Down
	const auto down = [this]()
	{
		if (m_step < m_tagSize)
		{
			m_tag[m_step]--;
			std::stringstream ss{};
			ss << m_tag[m_step];
			m_text[m_step]->SetText(ss.str());
		}
	};
	keyboardCommand = new LambdaCommand{ down };
	controllerCommand = new LambdaCommand{ down };
	input.BindCommand<LambdaCommand>(keyboardCommand, SDLK_DOWN, InputManager::InputType::OnButtonDown);
	input.BindCommand<LambdaCommand>(controllerCommand, 0, Controller::ControllerButton::DPadDown, InputManager::InputType::OnButtonDown);
	m_pCommands.push_back(keyboardCommand);
	m_pCommands.push_back(controllerCommand);
}

dae::GameOverManager::~GameOverManager()
{
	for (const auto command : m_pCommands)
	{
		InputManager::GetInstance().RemoveCommand(command);
	}
}

void dae::GameOverManager::Next()
{
	++m_step;
	
	switch (m_step)
	{
	case 1:
	case 2:
		break;
	case 3:
		{
		std::stringstream ss{};
		for (int i{}; i < m_tagSize; ++i) { ss << m_tag[i]; }
		ScoreManager::GetInstance().SubmitScore(ss.str());
		LoadScores();
		}
		break;
	default:
		MainMenuScene::Load();
		break;
	}
}

void dae::GameOverManager::LoadScores() const
{
	const auto& sceneManager = SceneManager::GetInstance();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	const auto screenWidth = static_cast<float>(sceneManager.GetWidth());
	const auto scores = ScoreManager::GetInstance().GetScores();
	for (int i{}; i < static_cast<int>(scores.size()); ++i)
	{
		const auto textObj = new GameObject();
		const auto textTitle = textObj->AddComponent<TextRenderer>(scores[i], font);
		const auto imageSize = textTitle->GetDimensions();
		textObj->GetComponent<Transform>()->SetPosition(screenWidth / 2.f - imageSize.x / 2.f, static_cast<float>(300 + i * 30));
		textObj->SetParent(GetGameObject(), false);
	}
}
