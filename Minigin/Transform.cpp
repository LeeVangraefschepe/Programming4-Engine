#include "Transform.h"
#include "GameObject.h"

void dae::Transform::SetPosition(const float x, const float y)
{
	m_localPosition.x = x;
	m_localPosition.y = y;
	SetPositionDirty();
}

void dae::Transform::SetLocalPosition(float x, float y)
{
	m_localPosition.x = x;
	m_localPosition.y = y;
	SetPositionDirty();
}

void dae::Transform::SetPositionDirty()
{
	const auto children = GetGameObject()->GetChildren();
	for (const auto child : children)
	{
		auto transfrom = child->GetComponent<Transform>();
		if (transfrom == nullptr)
		{
			continue;
		}
		transfrom->SetPositionDirty();
	}
	m_isPositionDirty = true;
}

const glm::vec2& dae::Transform::GetLocalPosition() const
{
	return m_localPosition;
}

const glm::vec2& dae::Transform::GetWorldPosition()
{
	if (m_isPositionDirty)
	{
		UpdateWorldPosition();
	}
	return m_worldPosition;
}

void dae::Transform::UpdateWorldPosition()
{
	if (GetGameObject()->GetParent() == nullptr)
	{
		m_worldPosition = m_localPosition;
	}
	else
	{
		const auto tranformParent = GetGameObject()->GetParent()->GetComponent<Transform>();
		const auto worldposParent = tranformParent->GetWorldPosition();
		m_worldPosition = worldposParent + m_localPosition;
	}
	m_isPositionDirty = false;
}