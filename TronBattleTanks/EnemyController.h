#pragma once
#include <glm/vec2.hpp>
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class HealthComponent;
	class Transform;
	class CollisionComponent;
	class EnemyVision;
	class SpriteRenderer;
	class ShootComponent;

	class EnemyController : public BaseComponent, Observer<EnemyVision>, Observer<HealthComponent>
	{
	public:
		explicit EnemyController(GameObject* pGameObject, float movementSpeed, int score);
		void Update() override;

		int GetScore() const { return m_score; }

		EnemyController(const EnemyController& other) = delete;
		EnemyController(EnemyController&& other) = delete;
		EnemyController& operator=(const EnemyController& other) = delete;
		EnemyController& operator=(EnemyController&& other) = delete;
	private:
		void HandleMovement();
		void HandleRotation() const;

		int m_score;
		float m_movementSpeed{};
		int m_direction{};
		glm::vec2 m_vectorDirection;
		static constexpr inline glm::vec2 DIRECTIONS[] =
		{
			glm::vec2(-1.0f, 0.0f), // left
			glm::vec2(0.0f, 1.0f), // top
			glm::vec2(1.0f, 0.0f), // right
			glm::vec2(0.0f, -1.0f) // bottom
		};

		void OnNotify(unsigned, EnemyVision*) override;
		void OnNotify(unsigned, HealthComponent*) override;

		Transform* m_pTransform;
		ShootComponent* m_pShoot;
		CollisionComponent* m_pCollision;
		SpriteRenderer* m_pSpriteRenderer;
	};

}