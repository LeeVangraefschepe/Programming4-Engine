#pragma once
#include <glm/vec2.hpp>
#include "BaseComponent.h"

namespace dae
{
	class Transform;
	class CollisionComponent final : public dae::BaseComponent
	{
	public:
		explicit CollisionComponent(dae::GameObject* pGameObject);
		~CollisionComponent() override;

		void SetSize(float width, float height);
		GameObject* IsColliding() const;
	private:
		static inline std::vector<CollisionComponent*> m_colliders{};

		glm::vec2 m_size{};
		Transform* m_transform;
	};
}