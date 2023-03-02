#pragma once
#include "RotateAroundComponent.h"
#include "GameObject.h"
#include "Time.h"

dae::RotateAroundComponent::RotateAroundComponent(GameObject* pGameObject, float radius, float speed) : m_radius(radius), m_speed(speed), UpdateComponent(pGameObject)
{
	m_pTransform = GetGameObject()->GetComponent<dae::Transform>();
	if (m_pTransform.expired())
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
	const auto transform = m_pTransform.lock();
	transform->SetLocalPosition(m_radius * cos(m_rotation * 3.14f / 180.f) + m_offset.x, m_radius * sin(m_rotation * 3.14f / 180.f) + m_offset.y);
}
