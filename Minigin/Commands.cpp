#include <glm/detail/func_geometric.inl>

#include "Commands.h"
#include "PlayerComponent.h"

void dae::MoveCommand::Execute()
{
	const auto& input = GetInput();
	if (glm::length(input) == 0.0f)
	{
		return;
	}
	m_pPlayerComponent->SetMovmentInput(input);
}

void dae::DebugDamage::Execute()
{
	m_pPlayerComponent->Damage(m_damage);
}