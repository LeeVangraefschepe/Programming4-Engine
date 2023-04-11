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
		explicit BulletComponent(GameObject* pGameObject, GameObject* pIgnore, const glm::vec2& direcion, float speed);

		void Update() override;
	private:
		GameObject* m_pIgnore;
		CollisionComponent* m_pCollision;
		Transform* m_pTransform;
		glm::vec2 m_direction;
		float m_speed;
	};
}
