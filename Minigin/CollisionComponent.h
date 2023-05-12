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
		const glm::vec2& GetSize() const { return m_size; }
		Transform* GetTransform() const { return m_transform; }
		GameObject* GetGameObject() const { return BaseComponent::GetGameObject(); }
	private:
		glm::vec2 m_size{};
		Transform* m_transform;
	};
}