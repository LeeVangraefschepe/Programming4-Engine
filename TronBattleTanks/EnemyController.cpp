#include "EnemyController.h"

#include <iostream>

#include "CellComponent.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "CollisionComponent.h"
#include "EnemyVision.h"
#include "Transform.h"
#include "Timer.h"
#include "HealthComponent.h"
#include "SpriteRenderer.h"
#include "ShootComponent.h"

dae::EnemyController::EnemyController(GameObject* pGameObject, float movementSpeed) : BaseComponent(pGameObject), m_movementSpeed(movementSpeed)
{
	m_vectorDirection = DIRECTIONS[m_direction];

	m_pCollision = pGameObject->GetComponent<CollisionComponent>();
	m_pTransform = pGameObject->GetComponent<Transform>();
	m_pSpriteRenderer = pGameObject->GetComponent<SpriteRenderer>();
	m_pShoot = pGameObject->AddComponent<ShootComponent>(&m_vectorDirection, 1.f);
	pGameObject->GetComponent<HealthComponent>()->GetSubject()->AddObserver(this);

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
	input *= Time::GetDeltaTime() * m_movementSpeed;

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
			m_vectorDirection = DIRECTIONS[m_direction];
			HandleRotation();
		}
	}

	//Apply position
	m_pTransform->SetLocalPosition(pos);
}

void dae::EnemyController::HandleRotation() const
{
	//Get input
	const glm::vec2 input = DIRECTIONS[m_direction];

	//Calculate the rotation angle in radians using atan2
	float rotation = glm::atan(input.y, input.x);
	rotation = glm::degrees(rotation);

	//Apply rotation to the sprite renderer
	m_pSpriteRenderer->SetRotation(rotation);
}

void dae::EnemyController::OnNotify(unsigned id, EnemyVision*)
{
	if (static_cast<EnemyVision::Event>(id) == EnemyVision::Fire)
	{
		m_pShoot->Shoot();
	}
}

void dae::EnemyController::OnNotify(unsigned id, HealthComponent*)
{
	if (static_cast<HealthComponent::Events>(id) == HealthComponent::died)
	{
		GetGameObject()->Destroy();
	}
}
