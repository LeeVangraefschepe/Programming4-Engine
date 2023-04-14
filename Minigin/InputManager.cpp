#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>
#include "InputManager.h"

#include <iostream>

bool dae::InputManager::ProcessInput()
{
	//Erased commands handling
	if (!m_removedCommands.empty())
	{
		for (const auto& command : m_removedCommands)
		{
			EraseCommand(command);
		}
		m_removedCommands.clear();
	}

	//Keyboard handling & application
	if (!ReadEvents()) { return false; }

	for (const auto& command : m_keyboardCommands)
	{
		bool canExecute{};
		switch (command.first)
		{
		case InputType::OnButtonDown:
			canExecute = m_keysDown.contains(command.second.first[0]);
			break;
		case InputType::OnButtonUp:
			canExecute = m_keysUp.contains(command.second.first[0]);
			break;
		case InputType::OnButton:
			canExecute = m_keysPressed.contains(command.second.first[0]);
			break;
		case InputType::Axis:
			{
				AxisCommand* axis = static_cast<AxisCommand*>(command.second.second.get());
				glm::vec2 input{};
				int index{-1};
				input.x -= static_cast<float>(m_keysPressed.contains(command.second.first[++index]));
				input.y += static_cast<float>(m_keysPressed.contains(command.second.first[++index]));
				input.x += static_cast<float>(m_keysPressed.contains(command.second.first[++index]));
				input.y -= static_cast<float>(m_keysPressed.contains(command.second.first[++index]));
				axis->SetInput(input);
				canExecute = true;
			}
			break;
		}
		if (canExecute)
		{
			command.second.second->Execute();
		}
	}

	//Controller handling
	for (const auto& pController : m_controllers)
	{
		pController->Update();
	}
	for (const auto& command : m_consoleCommands)
	{
		bool canExecute{};
		switch (command.first.inputType)
		{
		case InputType::OnButtonDown:
			canExecute = m_controllers[command.first.id]->IsDown(command.first.buttons[0]);
			break;
		case InputType::OnButtonUp:
			canExecute = m_controllers[command.first.id]->IsUp(command.first.buttons[0]);
			break;
		case InputType::OnButton:
			canExecute = m_controllers[command.first.id]->IsPressed(command.first.buttons[0]);
			break;
		case InputType::Axis:
			AxisCommand* axis = static_cast<AxisCommand*>(command.second.get());
			if (command.first.multipleButtons)
			{
				glm::vec2 input{};
				int index{ -1 };
				input.x -= static_cast<float>(m_controllers[command.first.id]->IsPressed(command.first.buttons[++index]));
				input.y += static_cast<float>(m_controllers[command.first.id]->IsPressed(command.first.buttons[++index]));
				input.x += static_cast<float>(m_controllers[command.first.id]->IsPressed(command.first.buttons[++index]));
				input.y -= static_cast<float>(m_controllers[command.first.id]->IsPressed(command.first.buttons[++index]));
				axis->SetInput(input);
			}
			else
			{
				axis->SetInput(m_controllers[command.first.id]->GetAxis(command.first.buttons[0]));
			}
			
			canExecute = true;
			break;
		}
		if (canExecute)
		{
			command.second->Execute();
		}
	}

	//Clear keyboard events
	ClearEvents();

	return true;
}
bool dae::InputManager::ReadEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		//Log keyboard inputs
		if (e.type == SDL_KEYDOWN)
		{
			m_keysDown.insert(e.key.keysym.sym);
			m_keysPressed.insert(e.key.keysym.sym);
		}
		if (e.type == SDL_KEYUP)
		{
			m_keysUp.insert(e.key.keysym.sym);
			m_keysPressed.erase(e.key.keysym.sym);
		}
		if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
		{
			m_keysPressed.clear();
		}

		//Quit loop condition
		if (e.type == SDL_QUIT)
		{
			return false;
		}

		//Get next event
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	return true;
}
void dae::InputManager::ClearEvents()
{
	m_keysDown.clear();
	m_keysUp.clear();
}
void dae::InputManager::EraseCommand(const Command* command)
{
	auto consoleIt = m_consoleCommands.begin();
	while (consoleIt != m_consoleCommands.end())
	{
		if (consoleIt->second && consoleIt->second.get() == command)
		{
			consoleIt = m_consoleCommands.erase(consoleIt);
		}
		else
		{
			++consoleIt;
		}
	}

	auto keyboardIt = m_keyboardCommands.begin();
	while (keyboardIt != m_keyboardCommands.end())
	{
		if (keyboardIt->second.second && keyboardIt->second.second.get() == command)
		{
			keyboardIt = m_keyboardCommands.erase(keyboardIt);
		}
		else
		{
			++keyboardIt;
		}
	}
}
void dae::InputManager::RemoveCommand(const Command* command)
{
	m_removedCommands.push_back(command);
}
int dae::InputManager::FindController(int id)
{
	const int size = static_cast<int>(m_controllers.size());
	if (id >= size)
	{
		m_controllers.push_back(std::make_unique<Controller>(static_cast<unsigned int>(size)));
		return size + 1;
	}
	return id;
}
