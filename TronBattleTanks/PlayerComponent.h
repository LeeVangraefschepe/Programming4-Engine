#pragma once
#include <glm/vec2.hpp>
#include <memory>
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class HealthComponent;
	class ScoreComponent;
	class SpriteRenderer;
	class Transform;
	class CollisionComponent;

	class PlayerComponent final : public BaseComponent, public Observer<HealthComponent>, public Observer<ScoreComponent>
	{
	public:
		enum Events
		{
			damage = 0,
			score,
			died
		};

		struct PlayerData
		{
			HealthComponent* healthComponent{nullptr};
			ScoreComponent* scoreComponent{nullptr};
		};

		explicit PlayerComponent(GameObject* pGameObject);
		void AddObservableObject(Observer<PlayerComponent>* observer) const;
		
		void SetMovmentInput(glm::vec2 input);
		void FireInput();
		void OnNotify(unsigned eventId, HealthComponent* entity) override;
		void OnNotify(unsigned eventId, ScoreComponent* entity) override;

		PlayerData* GetData() const;

	private:
		void HandleRotation() const;
		void HandleMovement(glm::vec2 input) const;

		Transform* m_pTransform;
		SpriteRenderer* m_pSpriteRenderer;
		CollisionComponent* m_pCollision;

		glm::vec2 m_direction{};

		std::unique_ptr<Subject<PlayerComponent>> m_subject = std::make_unique<Subject<PlayerComponent>>();
		GameObject* m_pRootObject;

		std::unique_ptr<PlayerData> m_pData = std::make_unique<PlayerData>();
	};
}
