#pragma once
#include <glm/vec2.hpp>
#include "BaseComponent.h"

namespace dae
{
	class Transform;
	class CollisionComponent;
	class BulletComponent final : public BaseComponent
	{
	public:
		explicit BulletComponent(GameObject* pGameObject, GameObject* pCreator, const glm::vec2& direction, float speed, float damage);

		void Update() override;
	private:
		GameObject* m_pCreator;
		CollisionComponent* m_pCollision;
		Transform* m_pTransform;
		glm::vec2 m_direction;
		float m_speed;
		float m_damage;
		float m_timeAlive{};
		float m_maxTimeAlive = 5.f;
	};
}
