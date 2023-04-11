#pragma once
#include <glm/vec2.hpp>
#include <memory>
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class HealthComponent;
	class SpriteRenderer;
	class Transform;
	class CollisionComponent;

	class PlayerComponent final : public BaseComponent, public Observer<HealthComponent>
	{
	public:
		explicit PlayerComponent(GameObject* pGameObject);
		void AddObservableObject(Observer<PlayerComponent>* observer) const;
		
		void SetMovmentInput(glm::vec2 input);
		void FireInput();
		void OnNotify(unsigned eventId, HealthComponent* entity) override;

	private:
		Transform* m_pTransform;
		SpriteRenderer* m_pSpriteRenderer;
		CollisionComponent* m_pCollision;

		std::unique_ptr<Subject<PlayerComponent>> m_subject = std::make_unique<Subject<PlayerComponent>>();
		GameObject* m_pRootObject;

		int m_direction{};
		static const inline glm::vec2 DIRECTIONS[] =
		{
			glm::vec2(-1.0f, 0.0f), // left
			glm::vec2(0.0f, 1.0f), // top
			glm::vec2(1.0f, 0.0f), // right
			glm::vec2(0.0f, -1.0f) // bottom
		};
	};
}
