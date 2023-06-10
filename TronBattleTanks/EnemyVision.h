#pragma once
#include <memory>
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class CollisionComponent;
	class EnemyVision : public BaseComponent
	{
	public:
		enum Event
		{
			Fire
		};

		explicit EnemyVision(GameObject* pGameObject, CollisionComponent* ignore, int* direction);

		void Update() override;
		Subject<EnemyVision>* GetSubject() const { return m_subject.get(); }

		EnemyVision(const EnemyVision& other) = delete;
		EnemyVision(EnemyVision&& other) = delete;
		EnemyVision& operator=(const EnemyVision& other) = delete;
		EnemyVision& operator=(EnemyVision&& other) = delete;
	private:
		CollisionComponent* DIRECTIONS[4]{};
		int* m_direction;

		std::unique_ptr<Subject<EnemyVision>> m_subject = std::make_unique<Subject<EnemyVision>>();

		std::vector<CollisionComponent*> m_pIgnore{};
	};
}