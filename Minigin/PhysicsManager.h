#pragma once
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
		GameObject* CheckCollisonClosest(const CollisionComponent* collision, const std::vector<CollisionComponent*>& ignores) const;
		GameObject* CheckCollisonClosest(const CollisionComponent* collision) const;
		GameObject* CheckCollision(const CollisionComponent* collision, const std::vector<CollisionComponent*>& ignores) const;
		GameObject* CheckCollision(const CollisionComponent* collision) const;
	private:
		friend class Singleton;
		PhysicsManager() = default;

		std::vector<CollisionComponent*> m_colliders{};
	};

}

