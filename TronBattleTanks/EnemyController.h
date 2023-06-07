#pragma once
#include <glm/vec2.hpp>
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class Transform;
	class CollisionComponent;
	class EnemyVision;

	class EnemyController : public BaseComponent, Observer<EnemyVision>
	{
	public:
		explicit EnemyController(GameObject* pGameObject);
		void Update() override;
		void HandleMovement();

		EnemyController(const EnemyController& other) = delete;
		EnemyController(EnemyController&& other) = delete;
		EnemyController& operator=(const EnemyController& other) = delete;
		EnemyController& operator=(EnemyController&& other) = delete;
	private:
		int m_direction{};
		static constexpr inline glm::vec2 DIRECTIONS[] =
		{
			glm::vec2(-1.0f, 0.0f), // left
			glm::vec2(0.0f, 1.0f), // top
			glm::vec2(1.0f, 0.0f), // right
			glm::vec2(0.0f, -1.0f) // bottom
		};

		void OnNotify(unsigned, EnemyVision*) override;

		Transform* m_pTransform;
		CollisionComponent* m_pCollision;
	};

}