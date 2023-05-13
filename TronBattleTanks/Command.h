#pragma once
#include <glm/vec2.hpp>

namespace dae
{
	class GameObject;
	class Command
	{
	public:
		explicit Command() = default;
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
		explicit AxisCommand() = default;
		virtual ~AxisCommand() override = default;
		virtual void Execute() override = 0;
		void SetInput(const glm::vec2& input) { m_input = input; }

		AxisCommand(const AxisCommand& other) = delete;
		AxisCommand(AxisCommand&& other) = delete;
		AxisCommand& operator=(const AxisCommand& other) = delete;
		AxisCommand& operator=(AxisCommand&& other) = delete;
	};
}

