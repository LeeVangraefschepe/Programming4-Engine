#include "Commands.h"
#include <iostream>
#include "Time.h"

void dae::MoveCommand::Execute()
{
	auto input = GetInput();
	input.y *= -1.f;
	if (glm::length(input) > 0.f)
	{
		input = glm::normalize(input);
	}
	input *= Time::GetDeltaTime() * m_Speed;

	auto pos = m_pTransform->GetLocalPosition();
	pos += input;
	m_pTransform->SetLocalPosition(pos);
}
