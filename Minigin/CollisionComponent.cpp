#include "CollisionComponent.h"
#include "GameObject.h"
#include "Transform.h"

dae::CollisionComponent::CollisionComponent(dae::GameObject* pGameObject) : BaseComponent(pGameObject)
{
	m_colliders.push_back(this);
	m_transform = GetGameObject()->GetComponent<Transform>();
}

dae::CollisionComponent::~CollisionComponent()
{
	for (auto it = m_colliders.begin(); it != m_colliders.end(); ++it)
	{
		if (*it == this)
		{
			m_colliders.erase(it);
			break;
		}
	}
}

void dae::CollisionComponent::SetSize(float width, float height)
{
	m_size.x = width;
	m_size.y = height;
}

dae::GameObject* dae::CollisionComponent::IsColliding() const
{
	const auto pos = m_transform->GetWorldPosition();
	for (const auto other : m_colliders)
	{
		if (other == this) {continue;}

		const auto otherPos = other->m_transform->GetWorldPosition();

		// Check if the two objects overlap
		if (pos.x < otherPos.x + other->m_size.x &&
			pos.x + m_size.x > otherPos.x &&
			pos.y < otherPos.y + other->m_size.y &&
			pos.y + m_size.y > otherPos.y)
		{
			// The two objects overlap
			return other->GetGameObject();
		}
	}
	return nullptr;
}
