#pragma once
#include <memory>
#include "Transform.h"
#include "BaseComponent.h"

namespace dae
{
	class RotateAroundComponent final : public BaseComponent
	{
	public:
		explicit RotateAroundComponent(GameObject* pGameObject, float radius, float speed);
		explicit RotateAroundComponent(GameObject* pGameObject, const glm::vec3& offset, float radius, float speed);

		~RotateAroundComponent() override = default;
		void Update() override;
	private:
		Transform* m_pTransform;
		Transform* m_pParentTransform;
		float m_radius;
		float m_rotation{};
		float m_speed;
		glm::vec3 m_offset{};
	};
}