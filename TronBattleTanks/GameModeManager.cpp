#include "GameModeManager.h"

#include <iostream>
#include <SDL_keycode.h>
#include <utility>
#include "Commands.h"
#include "GameObject.h"
#include "InputManager.h"
#include "GameScene.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "SpriteRenderer.h"

dae::GameModeManager::GameModeManager(GameObject* pGameObject, std::vector<glm::vec2> cursorPositions) : BaseComponent(pGameObject)
{
	m_positions = std::move(cursorPositions);
	auto& input = InputManager::GetInstance();

	const auto cursor = new GameObject();
	cursor->AddComponent<SpriteRenderer>(ResourceManager::GetInstance().LoadTexture("BlueTank.png"));
	m_pCursorTransfrom = cursor->GetComponent<Transform>();
	cursor->SetParent(pGameObject, false);

	const auto upAction = [this]()
	{
		m_selectedGameMode++;
		if (m_selectedGameMode > 2) { m_selectedGameMode = 2; }
		m_gamemode = static_cast<GameModes>(m_selectedGameMode);
		std::cout << "UPMENU\n";
	};
	auto keyboardCommand = new LambdaCommand{ upAction };
	auto controllerCommand = new LambdaCommand{ upAction };
	input.BindCommand<LambdaCommand>(keyboardCommand, SDLK_DOWN, InputManager::InputType::OnButtonDown);
	input.BindCommand<LambdaCommand>(controllerCommand, 0, Controller::ControllerButton::DPadDown, InputManager::InputType::OnButtonDown);
	m_commands.emplace_back(keyboardCommand);
	m_commands.emplace_back(controllerCommand);

	const auto downAction = [this]()
	{
		m_selectedGameMode--;
		if (m_selectedGameMode < 0) { m_selectedGameMode = 0; }
		m_gamemode = static_cast<GameModes>(m_selectedGameMode);
		std::cout << "DOWNMENU\n";
	};
	keyboardCommand = new LambdaCommand{ downAction };
	controllerCommand = new LambdaCommand{ downAction };
	input.BindCommand<LambdaCommand>(keyboardCommand, SDLK_UP, InputManager::InputType::OnButtonDown);
	input.BindCommand<LambdaCommand>(controllerCommand, 0, Controller::ControllerButton::DPadUp, InputManager::InputType::OnButtonDown);
	m_commands.emplace_back(keyboardCommand);
	m_commands.emplace_back(controllerCommand);

	const auto continueAction = [this]()
	{
		GameScene::Load();
	};
	keyboardCommand = new LambdaCommand{ continueAction };
	controllerCommand = new LambdaCommand{ continueAction };
	input.BindCommand<LambdaCommand>(keyboardCommand, SDLK_a, InputManager::InputType::OnButtonDown);
	input.BindCommand<LambdaCommand>(controllerCommand, 0, Controller::ControllerButton::ButtonA, InputManager::InputType::OnButtonDown);
	m_commands.emplace_back(keyboardCommand);
	m_commands.emplace_back(controllerCommand);
}

dae::GameModeManager::~GameModeManager()
{
	auto& input = InputManager::GetInstance();
	for (const auto& command : m_commands)
	{
		input.RemoveCommand(command);
	}
}

void dae::GameModeManager::Update()
{
	m_pCursorTransfrom->SetLocalPosition(m_positions[m_selectedGameMode]);
}
