#include <glm/detail/func_geometric.inl>

#include "Commands.h"

#include "InputManager.h"
#include "PlayerComponent.h"

void dae::MoveCommand::Execute()
{
	const auto& input = GetInput();
	if (length(input) == 0.0f)
	{
		return;
	}
	m_pPlayerComponent->SetMovmentInput(input);
}

void dae::MoveCommand::OnDestroy()
{
	InputManager::GetInstance().RemoveCommand(this);
}

void dae::FireCommand::Execute()
{
	m_pPlayerComponent->FireInput();
}

void dae::FireCommand::OnDestroy()
{
	InputManager::GetInstance().RemoveCommand(this);
}
