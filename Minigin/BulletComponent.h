#pragma once
#include <glm/vec2.hpp>
#include "BaseComponent.h"

namespace dae
{
	class BulletComponent final : public BaseComponent
	{
	public:
		explicit BulletComponent(GameObject* pGameObject, const glm::vec2& direcion, float speed);

		void Update() override;
	private:
		GameObject* m_rootObject;
		glm::vec2 m_direction;
		float m_speed;
	};
}
