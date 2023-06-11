#include "GameOverManager.h"

#include <SDL_keycode.h>

#include "Commands.h"
#include "InputManager.h"
#include "MainMenuScene.h"

dae::GameOverManager::GameOverManager(GameObject* pGameObject) : BaseComponent(pGameObject)
{
	auto& input = InputManager::GetInstance();

	const auto keyboardCommand = new LambdaCommand
	{
		[this]()
		{
			MainMenuScene::Load();
		}
	};
	const auto controllerCommand = new LambdaCommand
	{
		[this]()
		{
			MainMenuScene::Load();
		}
	};
	input.BindCommand<LambdaCommand>(keyboardCommand, SDLK_a, InputManager::InputType::OnButtonDown);
	input.BindCommand<LambdaCommand>(controllerCommand, 0, Controller::ControllerButton::ButtonA, InputManager::InputType::OnButtonDown);
	m_pKeyboardCommand = keyboardCommand;
	m_pControllerCommand = controllerCommand;
}

dae::GameOverManager::~GameOverManager()
{
	InputManager::GetInstance().RemoveCommand(m_pKeyboardCommand);
	InputManager::GetInstance().RemoveCommand(m_pControllerCommand);
}
