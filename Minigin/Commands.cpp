#include "Commands.h"
#include <iostream>
#include "Time.h"

void dae::MoveCommand::Execute()
{
	auto input = GetInput();
	input.y *= -1.f;
	input *= Time::GetDeltaTime() * m_Speed;

	auto pos = m_pTransform->GetLocalPosition();
	pos += input;
	m_pTransform->SetLocalPosition(pos);
}