#include "GameModeManager.h"

#include <iostream>
#include <SDL_keycode.h>
#include <utility>
#include "Commands.h"
#include "InputManager.h"
#include "GameScene.h"

dae::GameModeManager::GameModeManager(GameObject* pGameObject, std::vector<glm::vec2> cursorPositions) : BaseComponent(pGameObject)
{
	m_positions = std::move(cursorPositions);
	auto& input = InputManager::GetInstance();

	auto command = new LambdaCommand
	{
		[this]()
		{
			std::cout << "UP\n";
		}
	};
	input.BindCommand<LambdaCommand>(command, SDLK_UP, InputManager::InputType::OnButtonDown);
	m_commands.emplace_back(command);

	command = new LambdaCommand
	{
		[this]()
		{
			GameScene::Load();
		}
	};
	input.BindCommand<LambdaCommand>(command, SDLK_RETURN, InputManager::InputType::OnButtonDown);
	m_commands.emplace_back(command);
}

dae::GameModeManager::~GameModeManager()
{
	auto& input = InputManager::GetInstance();
	for (const auto& command : m_commands)
	{
		input.RemoveCommand(command);
	}
}
