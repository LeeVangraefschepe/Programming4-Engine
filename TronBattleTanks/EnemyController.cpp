#include "EnemyController.h"

#include <iostream>

#include "CellComponent.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "CollisionComponent.h"
#include "EnemyVision.h"
#include "Transform.h"
#include "Timer.h"

dae::EnemyController::EnemyController(GameObject* pGameObject) : BaseComponent(pGameObject)
{
	m_pCollision = pGameObject->GetComponent<CollisionComponent>();
	m_pTransform = pGameObject->GetComponent<Transform>();

	const glm::vec2 size = m_pCollision->GetSize();
	const auto vision = new GameObject{};
	vision->AddComponent<EnemyVision>(m_pCollision, &m_direction)->GetSubject()->AddObserver(this);
	vision->SetParent(pGameObject, false);
	vision->GetComponent<Transform>()->SetLocalPosition(size.x/2.f, size.y/2.f);
}

void dae::EnemyController::Update()
{
	HandleMovement();
}

void dae::EnemyController::HandleMovement()
{
	//Apply movement speed
	glm::vec2 input = DIRECTIONS[m_direction];
	constexpr float movementSpeed{ 50.f };
	input *= Time::GetDeltaTime() * movementSpeed;

	//Get position
	auto pos = m_pTransform->GetLocalPosition();
	pos += input;

	//Check wall collision
	if (const auto other = PhysicsManager::GetInstance().CheckCollision(m_pCollision); other)
	{
		if (other->HasComponent<CellComponent>())
		{
			const auto wallPos = other->GetComponent<Transform>()->GetWorldPosition();
			pos = m_pTransform->GetLocalPosition();
			auto direction = pos - wallPos;
			direction = glm::normalize(direction);
			pos += direction;

			m_direction = rand() % 4;
		}
	}

	//Apply position
	m_pTransform->SetLocalPosition(pos);
}

void dae::EnemyController::OnNotify(unsigned id, EnemyVision*)
{
	if (static_cast<EnemyVision::Event>(id) == EnemyVision::Fire)
	{
		std::cout << "Shoot\n";
	}
}
