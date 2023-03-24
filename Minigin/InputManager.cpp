#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>
#include "InputManager.h"

bool dae::InputManager::ProcessInput()
{
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
			canExecute = m_controllers[command.first.id]->IsDown(command.first.button);
			break;
		case InputType::OnButtonUp:
			canExecute = m_controllers[command.first.id]->IsUp(command.first.button);
			break;
		case InputType::OnButton:
			canExecute = m_controllers[command.first.id]->IsPressed(command.first.button);
			break;
		case InputType::Axis:
			AxisCommand* axis = static_cast<AxisCommand*>(command.second.get());
			axis->SetInput(m_controllers[command.first.id]->GetAxis(command.first.button));
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
