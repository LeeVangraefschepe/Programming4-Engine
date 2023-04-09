#pragma once
#include "Command.h"
#include "PlayerComponent.h"

namespace dae
{
	class Transform;
	class PlayerComponent;

	class MoveCommand final : public AxisCommand
	{
	public:
		MoveCommand(dae::PlayerComponent* pplayer) : m_pPlayerComponent(pplayer){}
		~MoveCommand() override = default;
		void Execute() override;
	private:
		PlayerComponent* m_pPlayerComponent;
	};

	class DebugDamage final : public Command
	{
	public:
		DebugDamage(PlayerComponent* pplayer, float damage = 1.f) : m_pPlayerComponent(pplayer), m_damage(damage){}
		~DebugDamage() override = default;
		void Execute() override;
	private:
		PlayerComponent* m_pPlayerComponent;
		float m_damage;
	};
}
