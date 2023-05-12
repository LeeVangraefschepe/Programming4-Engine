#include "PhysicsManager.h"
#include "Transform.h"

void dae::PhysicsManager::AddCollider(CollisionComponent* collision)
{
	for (auto it = m_colliders.begin(); it != m_colliders.end(); ++it)
	{
		if (*it == collision)
		{
			return; //Collider already added
		}
	}
	m_colliders.push_back(collision);
}

void dae::PhysicsManager::RemoveCollider(const CollisionComponent* collision)
{
	for (auto it = m_colliders.begin(); it != m_colliders.end(); ++it)
	{
		if (*it == collision)
		{
			m_colliders.erase(it);
			break;
		}
	}
}

dae::GameObject* dae::PhysicsManager::CheckCollision(const CollisionComponent* collision) const
{
	const auto transform = collision->GetTransform();
	const auto pos = transform->GetWorldPosition();
	const auto size = collision->GetSize();
	for (const auto& other : m_colliders)
	{
		if (other == collision) {continue;} //Don't check yourself

		const auto otherPos = other->GetTransform()->GetWorldPosition();
		const auto otherSize = other->GetSize();

		//Check if the two objects overlap
		if (pos.x < otherPos.x + otherSize.x &&
			pos.x + size.x > otherPos.x &&
			pos.y < otherPos.y + otherSize.y &&
			pos.y + size.y > otherPos.y)
		{
			return other->GetGameObject(); //Overlap
		}
	}

	return nullptr;
}
