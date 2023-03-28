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
		void RemoveCommands(const GameObject* pGameObject);

		template <class T>
		T* BindCommand(int id, Controller::ControllerButton button, InputType inputType, GameObject* pGameObject)
		{
			//Check if class is right & get or create the controller
			static_assert(std::is_base_of<Command, T>(), "T needs to be derived from command");
			FindController(id);

			//Check if Command is Axis usable
			if (inputType == InputType::Axis && std::is_base_of<AxisCommand, T>() == false)
			{
				return nullptr;
			}

			//Create the command and key
			auto command = std::make_unique<T>(pGameObject);
			ControllerKey key{ id, inputType, std::vector{button} };

			//Cache the raw pointer for return
			T* rawPointer = command.get();

			//Add to multimap
			m_consoleCommands.emplace(key, std::move(command));

			//Return raw pointer pointing towards the command
			return rawPointer;
		}
		template <class T>
		T* BindCommand(unsigned key, InputType inputType, GameObject* pGameObject)
		{
			//Check if class is right & input type is correctly
			static_assert(std::is_base_of<Command, T>(), "T needs to be derived from command");
			assert(InputType::Axis != inputType && "Can not bind Axis with one value");
			if (InputType::Axis == inputType)
			{
				return nullptr;
			}

			//Create & cache the raw pointer for return
			auto command = std::make_unique<T>(pGameObject);
			T* rawPointer = command.get();

			//Add to multimap with one key
			m_keyboardCommands.emplace(inputType, KeyboardBinding{ std::vector{key}, std::move(command) });

			//Return raw pointer pointing towards the command
			return rawPointer;
		}
		template <class T>
		T* BindCommand(int id, Controller::ControllerButton left, Controller::ControllerButton up, Controller::ControllerButton right, Controller::ControllerButton bottom, InputType inputType, GameObject* pGameObject)
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
			auto command = std::make_unique<T>(pGameObject);
			ControllerKey key{ id, inputType, std::vector{left, up, right, bottom}, true };

			//Cache the raw pointer for return
			T* rawPointer = command.get();

			//Add to multimap
			m_consoleCommands.emplace(key, std::move(command));

			//Return raw pointer pointing towards the command
			return rawPointer;
		}
		template <class T>
		T* BindCommand(unsigned left, unsigned up, unsigned right, unsigned down, InputType inputType, GameObject* pGameObject)
		{
			//Check if class is right & input type is correctly
			static_assert(std::is_base_of<AxisCommand, T>(), "T needs to be derived from command");
			assert(InputType::Axis == inputType && "Can not bind Button with multiple values");
			if (InputType::Axis != inputType)
			{
				return nullptr;
			}

			//Create & cache the raw pointer for return
			auto command = std::make_unique<T>(pGameObject);
			T* rawPointer = command.get();

			//Add to multimap with four keys
			m_keyboardCommands.emplace(inputType, KeyboardBinding{ std::vector{left,up,right,down} ,std::move(command) });

			//Return raw pointer pointing towards the command
			return rawPointer;
		}

	private:
		void ClearEvents();
		int FindController(int);
		bool ReadEvents();
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
