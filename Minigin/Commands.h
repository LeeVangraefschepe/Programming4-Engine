#pragma once
#include "Command.h"
#include "GameObject.h"

class Transform;

namespace dae
{
	class MoveCommand final : public AxisCommand
	{
	public:
		MoveCommand(GameObject* actor) : AxisCommand(actor), m_pTransform(actor->GetComponent<Transform>()) {}
		~MoveCommand() override = default;
		void SetSpeed(float speed) { m_Speed = speed; }
		void Execute() override;
	private:
		Transform* m_pTransform;
		float m_Speed{10.f};
	};
}