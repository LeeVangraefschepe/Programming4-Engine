#include "Transform.h"
#include "GameObject.h"

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_localPosition.x = x;
	m_localPosition.y = y;
	m_localPosition.z = z;
	SetPositionDirty();
}

void dae::Transform::SetLocalPosition(float x, float y, float z)
{
	m_localPosition.x = x;
	m_localPosition.y = y;
	m_localPosition.z = z;
	SetPositionDirty();
}

void dae::Transform::SetPositionDirty()
{
	const auto children = GetGameObject()->GetChildren();
	for (const auto child : children)
	{
		auto transfrom = child.lock()->GetComponent<Transform>();
		if (transfrom.expired())
		{
			continue;
		}
		transfrom.lock()->SetPositionDirty();
	}
	m_isPositionDirty = true;
}

const glm::vec3& dae::Transform::GetWorldPosition()
{
	if (m_isPositionDirty)
	{
		UpdateWorldPosition();
	}
	return m_worldPosition;
}

void dae::Transform::UpdateWorldPosition()
{
	if (GetGameObject()->GetParent().expired())
	{
		m_worldPosition = m_localPosition;
	}
	else
	{
		const auto tranformParent = GetGameObject()->GetParent().lock()->GetComponent<Transform>().lock();
		const auto worldposParent = tranformParent->GetWorldPosition();
		m_worldPosition = worldposParent + m_localPosition;
	}
	m_isPositionDirty = false;
}