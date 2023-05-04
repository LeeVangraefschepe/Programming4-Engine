#pragma once
#include "RotateAroundComponent.h"
#include "GameObject.h"
#include "Timer.h"

dae::RotateAroundComponent::RotateAroundComponent(GameObject* pGameObject, float radius, float speed) : m_radius(radius), m_speed(speed), BaseComponent(pGameObject)
{
	m_pTransform = GetGameObject()->GetComponent<dae::Transform>();
	if (m_pTransform == nullptr)
	{
		m_pTransform = GetGameObject()->AddComponent<Transform>();
	}
}

dae::RotateAroundComponent::RotateAroundComponent(GameObject* pGameObject, const glm::vec3& offset, float radius, float speed) : RotateAroundComponent(pGameObject, radius, speed)
{
	m_offset = offset;
}

void dae::RotateAroundComponent::Update()
{
	m_rotation += Time::GetDeltaTime() * m_speed;
	m_pTransform->SetLocalPosition(m_radius * cos(m_rotation * 3.14f / 180.f) + m_offset.x, m_radius * sin(m_rotation * 3.14f / 180.f) + m_offset.y);
}
