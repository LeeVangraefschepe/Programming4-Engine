#pragma once
#include <glm/vec2.hpp>

namespace dae
{
	class GameObject;
	class Command
	{
		GameObject* m_actor;
	protected:
		GameObject* GetActor() const { return m_actor; }
	public:
		explicit Command(GameObject* actor) : m_actor(actor){}
		virtual ~Command() = default;
		virtual void Execute() = 0;

		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;
	};
	class AxisCommand : public Command
	{
		glm::vec2 m_input{};
	protected:
		glm::vec2& GetInput() { return m_input; }
	public:
		explicit AxisCommand(GameObject* actor) : Command(actor){}
		virtual ~AxisCommand() override = default;
		virtual void Execute() override = 0;
		void SetInput(const glm::vec2& input) { m_input = input; }

		AxisCommand(const AxisCommand& other) = delete;
		AxisCommand(AxisCommand&& other) = delete;
		AxisCommand& operator=(const AxisCommand& other) = delete;
		AxisCommand& operator=(AxisCommand&& other) = delete;
	};
}

