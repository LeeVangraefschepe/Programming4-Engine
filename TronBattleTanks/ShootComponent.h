#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

namespace dae
{
	class Transform;
	class ShootComponent : public BaseComponent
	{
	public:
		ShootComponent(GameObject* pGameObject, const glm::vec2* direction, float delay);
		void Update() override;

		void Shoot();

		ShootComponent(const ShootComponent& other) = delete;
		ShootComponent(ShootComponent&& other) = delete;
		ShootComponent& operator=(const ShootComponent& other) = delete;
		ShootComponent& operator=(ShootComponent&& other) = delete;
	private:
		Transform* m_pTransform;
		const glm::vec2* m_direction;
		const float m_maxDelay;
		float m_currentDelay{};
	};
}