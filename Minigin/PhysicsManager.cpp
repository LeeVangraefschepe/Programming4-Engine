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

dae::GameObject* dae::PhysicsManager::CheckCollisonClosest(const CollisionComponent* collision, const std::vector<CollisionComponent*>& ignores) const
{
	const auto transform = collision->GetTransform();
	const auto pos = transform->GetWorldPosition();
	const auto size = collision->GetSize();
	GameObject* closestObject = nullptr;
	float closestDistance = std::numeric_limits<float>::max();

	for (const auto& other : m_colliders)
	{
		if (other == collision) { continue; } //Don't check yourself

		bool isIgnore{};
		for (const auto& ingore : ignores)
		{
			if (other == ingore) { isIgnore = true; }
		}
		if (isIgnore) { continue; }


		const auto otherPos = other->GetTransform()->GetWorldPosition();
		const auto otherSize = other->GetSize();

		//Check if the two objects overlap
		if (pos.x < otherPos.x + otherSize.x &&
			pos.x + size.x > otherPos.x &&
			pos.y < otherPos.y + otherSize.y &&
			pos.y + size.y > otherPos.y)
		{
			//Calculate the distance between the centers of the objects
			const float distance = glm::distance(pos, otherPos);

			//Update the closest object if this object is closer
			if (distance < closestDistance)
			{
				closestObject = other->GetGameObject();
				closestDistance = distance;
			}
		}
	}

	return closestObject;
}

dae::GameObject* dae::PhysicsManager::CheckCollisonClosest(const CollisionComponent* collision) const
{
	return CheckCollisonClosest(collision, std::vector<CollisionComponent*>{});
}

dae::GameObject* dae::PhysicsManager::CheckCollision(const CollisionComponent* collision, const std::vector<CollisionComponent*>& ignores) const
{
	const auto transform = collision->GetTransform();
	const auto pos = transform->GetWorldPosition();
	const auto size = collision->GetSize();
	for (const auto& other : m_colliders)
	{
		if (other == collision) {continue;} //Don't check yourself

		bool isIgnore{};
		for (const auto& ingore : ignores)
		{
			if (other == ingore) { isIgnore = true; }
		}
		if (isIgnore) { continue; }
		

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

dae::GameObject* dae::PhysicsManager::CheckCollision(const CollisionComponent* collision) const
{
	return CheckCollision(collision, std::vector<CollisionComponent*>{});
}
