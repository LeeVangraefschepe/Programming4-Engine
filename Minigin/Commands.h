#pragma once
#include "Command.h"
#include "GameObject.h"

namespace dae
{
	class Transform;
	class MoveCommand final : public AxisCommand
	{
	public:
		MoveCommand(dae::Transform* transform, float speed = 100.f) : m_pTransform(transform), m_Speed(speed) {}
		~MoveCommand() override = default;
		void SetSpeed(float speed) { m_Speed = speed; }
		void Execute() override;
	private:
		Transform* m_pTransform;
		float m_Speed;
	};
}