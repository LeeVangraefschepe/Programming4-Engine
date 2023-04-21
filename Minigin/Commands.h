#pragma once
#include "Command.h"
#include "PlayerComponent.h"

namespace dae
{
	class Transform;
	class PlayerComponent;

	template<typename T>
	class Observer;

	class MoveCommand final : public AxisCommand, public Observer<PlayerComponent>
	{
	public:
		MoveCommand(PlayerComponent* pplayer) : m_pPlayerComponent(pplayer) { m_pPlayerComponent->AddObservableObject(this); }
		void Execute() override;
		void OnNotify(unsigned, PlayerComponent*) override{}
		void OnDestroy() override;
	private:
		PlayerComponent* m_pPlayerComponent;
	};

	class FireCommand : public Command, public Observer<PlayerComponent>
	{
	public:
		FireCommand(PlayerComponent* pplayer) : m_pPlayerComponent(pplayer){ m_pPlayerComponent->AddObservableObject(this); }
		void Execute() override;
		void OnNotify(unsigned, PlayerComponent*) override {}
		void OnDestroy() override;
	private:
		PlayerComponent* m_pPlayerComponent;

	};
}
