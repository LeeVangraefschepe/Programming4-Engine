#pragma once
#include <map>
#include "Singleton.h"
#include "CollisionComponent.h"

namespace dae
{
	class GameObject;
	class PhysicsManager : public Singleton<PhysicsManager>
	{
	public:
		void AddCollider(CollisionComponent* collision);
		void RemoveCollider(const CollisionComponent* collision);
		GameObject* CheckCollisonClosest(const CollisionComponent* collision, const std::vector<CollisionComponent*>& ignores);
		GameObject* CheckCollisonClosest(const CollisionComponent* collision);
		GameObject* CheckCollision(const CollisionComponent* collision, const std::vector<CollisionComponent*>& ignores);
		GameObject* CheckCollision(const CollisionComponent* collision);
	private:
		friend class Singleton;
		PhysicsManager() = default;
		std::map<int, std::vector<CollisionComponent*>> m_layers{};
	};
}