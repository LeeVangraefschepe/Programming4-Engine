#pragma once
#include <map>
#include "Singleton.h"
#include <memory>
#include <set>
#include <vector>
#include "Command.h"
#include "Controller.h"

namespace dae
{
	class GameObject;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		enum class InputType
		{
			OnButtonDown,
			OnButtonUp,
			OnButton,
			Axis
		};

		bool ProcessInput();
		void RemoveCommand(const Command* command);

#pragma region Controller
		template <class T>
		T* BindCommand(T* rawCommand, int id, Controller::ControllerButton button, InputType inputType)
		{
			//Check if class is right & get or create the controller
			static_assert(std::is_base_of<Command, T>(), "T needs to be derived from command");
			FindController(id);

			//Check if Command is Axis usable
			if (inputType == InputType::Axis && std::is_base_of<AxisCommand, T>() == false)
			{
				return nullptr;
			}

			ControllerKey key{ id, inputType, std::vector{button} };
			auto command = std::unique_ptr<T>(rawCommand);

			//Add to multimap
			m_consoleCommands.emplace(key, std::move(command));

			//Return raw pointer pointing towards the command
			return rawCommand;
		}

		template <class T>
		T* BindCommand(T* rawCommand, int id, Controller::ControllerButton left, Controller::ControllerButton up, Controller::ControllerButton right, Controller::ControllerButton bottom, InputType inputType)
		{
			//Check if class is right & get or create the controller
			static_assert(std::is_base_of<Command, T>(), "T needs to be derived from command");
			FindController(id);

			//Check if Command is Axis usable
			if (inputType != InputType::Axis || std::is_base_of<AxisCommand, T>() == false)
			{
				return nullptr;
			}

			//Create the command and key
			auto command = std::unique_ptr<T>(rawCommand);
			ControllerKey key{ id, inputType, std::vector{left, up, right, bottom}, true };

			//Add to multimap
			m_consoleCommands.emplace(key, std::move(command));

			//Return raw pointer pointing towards the command
			return rawCommand;
		}
#pragma endregion
#pragma region Keyboard
		template <class T>
		T* BindCommand(T* rawCommand, unsigned key, InputType inputType)
		{
			//Check if class is right & input type is correctly
			static_assert(std::is_base_of<Command, T>(), "T needs to be derived from command");
			assert(InputType::Axis != inputType && "Can not bind Axis with one value");
			if (InputType::Axis == inputType)
			{
				return nullptr;
			}

			//Create & cache the raw pointer for return
			auto command = std::unique_ptr<T>(rawCommand);

			//Add to multimap with one key
			m_keyboardCommands.emplace(inputType, KeyboardBinding{ std::vector{key}, std::move(command) });

			//Return raw pointer pointing towards the command
			return rawCommand;
		}
#pragma endregion 
		
		
		
		template <class T>
		T* BindCommand(T* rawCommand, unsigned left, unsigned up, unsigned right, unsigned down, InputType inputType)
		{
			//Check if class is right & input type is correctly
			static_assert(std::is_base_of<AxisCommand, T>(), "T needs to be derived from command");
			assert(InputType::Axis == inputType && "Can not bind Button with multiple values");
			if (InputType::Axis != inputType)
			{
				return nullptr;
			}

			//Create & cache the raw pointer for return
			auto command = std::unique_ptr<T>(rawCommand);

			//Add to multimap with four keys
			m_keyboardCommands.emplace(inputType, KeyboardBinding{ std::vector{left,up,right,down} ,std::move(command) });

			//Return raw pointer pointing towards the command
			return rawCommand;
		}

	private:
		void ClearEvents();
		void EraseCommand(const Command* command);
		int FindController(int);
		bool ReadEvents();
		std::vector<const Command*> m_removedCommands{};
#pragma region ControllerData
		struct ControllerKey
		{
			int id;
			InputType inputType;
			std::vector<Controller::ControllerButton> buttons;
			bool multipleButtons{false};
		public:
			bool operator<(const ControllerKey& other) const { return other.id < id; }
		};
		using ControllerCommandsMap = std::multimap<ControllerKey, std::unique_ptr<Command>>;
		ControllerCommandsMap m_consoleCommands{};

		std::vector<std::unique_ptr<Controller>> m_controllers{};
#pragma endregion
#pragma region KeyboardData
		using KeyboardBinding = std::pair<std::vector<unsigned>, std::unique_ptr<Command>>;
		using KeyboardCommandsMap = std::multimap<InputType, KeyboardBinding>;

		KeyboardCommandsMap m_keyboardCommands{};
		std::set<unsigned> m_keysDown{};
		std::set<unsigned> m_keysUp{};
		std::set<unsigned> m_keysPressed{};
#pragma endregion
	};
}
