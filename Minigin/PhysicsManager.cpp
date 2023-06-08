#include "PhysicsManager.h"

#include <ranges>

#include "Transform.h"

void dae::PhysicsManager::AddCollider(CollisionComponent* collision)
{
	const auto& layers = collision->GetLayers();

	for (const int layer : layers)
	{
		if (!m_layers.contains(layer))
		{
			m_layers.insert(std::pair{layer, std::vector<CollisionComponent*>{}});
		}

		for (auto it = m_layers[layer].begin(); it != m_layers[layer].end(); ++it)
		{
			if (*it == collision)
			{
				return; //Collider already added
			}
		}
		m_layers[layer].push_back(collision);
	}
}

void dae::PhysicsManager::RemoveCollider(const CollisionComponent* collision)
{
	const auto& layers = collision->GetLayers();
	for (const int layer : layers)
	{
		auto& colliders = m_layers[layer];

		for (auto it = colliders.begin(); it != colliders.end(); ++it)
		{
			if (*it == collision)
			{
				colliders.erase(it);
				break;
			}
		}
	}
}

dae::GameObject* dae::PhysicsManager::CheckCollisonClosest(const CollisionComponent* collision, const std::vector<CollisionComponent*>& ignores)
{
	const auto transform = collision->GetTransform();
	const auto pos = transform->GetWorldPosition();
	const auto size = collision->GetSize();
	GameObject* closestObject = nullptr;
	float closestDistance = std::numeric_limits<float>::max();

	const auto& layers = collision->GetLayers();
	for (const int layer : layers)
	{
		const auto& colliders = m_layers[layer];

		for (const auto& other : colliders)
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
	}

	return closestObject;
}

dae::GameObject* dae::PhysicsManager::CheckCollisonClosest(const CollisionComponent* collision)
{
	return CheckCollisonClosest(collision, std::vector<CollisionComponent*>{});
}

dae::GameObject* dae::PhysicsManager::CheckCollision(const CollisionComponent* collision, const std::vector<CollisionComponent*>& ignores)
{
	const auto transform = collision->GetTransform();
	const auto pos = transform->GetWorldPosition();
	const auto size = collision->GetSize();

	const auto& layers = collision->GetLayers();
	for (const int layer : layers)
	{
		const auto& colliders = m_layers[layer];
		for (const auto& other : colliders)
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
				return other->GetGameObject(); //Overlap
			}
		}

	}

	return nullptr;
}

dae::GameObject* dae::PhysicsManager::CheckCollision(const CollisionComponent* collision)
{
	return CheckCollision(collision, std::vector<CollisionComponent*>{});
}
