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

	class FireCommand : public Command
	{
	public:
		FireCommand(PlayerComponent* pplayer) : m_pPlayerComponent(pplayer){}
		~FireCommand() override = default;
		void Execute() override;
	private:
		PlayerComponent* m_pPlayerComponent;

	};
}
