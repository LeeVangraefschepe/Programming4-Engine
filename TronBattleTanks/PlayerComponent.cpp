#include "PlayerComponent.h"

#include <iostream>

#include "AudioManager.h"
#include "GameObject.h"
#include "BulletComponent.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"
#include "PhysicsManager.h"
#include "SceneManager.h"
#include "ScoreComponent.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Timer.h"
#include "CellComponent.h"
#include "DiamondCell.h"
#include "ServiceLocator.h"
#include "ShootComponent.h"

dae::PlayerComponent::PlayerComponent(GameObject* pGameObject) : BaseComponent(pGameObject)
{
	m_pData->healthComponent = pGameObject->GetComponent<HealthComponent>();
	m_pData->scoreComponent = pGameObject->GetComponent<ScoreComponent>();
	m_pData->healthComponent->GetSubject()->AddObserver(this);
	m_pData->scoreComponent->GetSubject()->AddObserver(this);

	m_pTransform = pGameObject->GetComponent<Transform>();
	m_pSpriteRenderer = pGameObject->GetComponent<SpriteRenderer>();
	m_pCollision = pGameObject->GetComponent<CollisionComponent>();
	m_pShoot = pGameObject->AddComponent<ShootComponent>(&m_direction, 1.f);

	m_pRootObject = SceneManager::GetInstance().GetActiveScene()->GetRootObject();
}
void dae::PlayerComponent::AddObservableObject(Observer<PlayerComponent>* observer) const
{
	m_subject->AddObserver(observer);
}
void dae::PlayerComponent::SetMovmentInput(glm::vec2 input)
{
	//Inverse Y direction
	input.y *= -1.f;

	//Set direction
	m_direction = glm::normalize(input);

	HandleRotation();
	HandleMovement(input);
}

void dae::PlayerComponent::FireInput() const
{
	m_pShoot->Shoot();
}

void dae::PlayerComponent::OnNotify(unsigned eventId, HealthComponent*)
{
	m_subject->Notify(Events::damage, this);
	if (eventId == HealthComponent::Events::died)
	{
		m_subject->Notify(Events::died, this);
		GetGameObject()->Destroy();
	}
}
void dae::PlayerComponent::OnNotify(unsigned, ScoreComponent*)
{
	m_subject->Notify(Events::score, this);
}

dae::PlayerComponent::PlayerData* dae::PlayerComponent::GetData() const
{
	return m_pData.get();
}

void dae::PlayerComponent::HandleRotation() const
{
	//Calculate the rotation angle in radians using atan2
	float rotation = glm::atan(m_direction.y, m_direction.x);
	rotation = glm::degrees(rotation);

	//Apply rotation to the sprite renderer
	m_pSpriteRenderer->SetRotation(rotation);
}

void dae::PlayerComponent::HandleMovement(glm::vec2 input)
{
	//Apply movement speed
	constexpr float movementSpeed{ 100.f };
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
		}
		else if (other->HasComponent<DiamondCell>())
		{
			m_subject->Notify(teleport, this);
			ServiceLocator::GetAudioSystem()->Play(AudioManager::Sounds::Teleport, 1.f);
			return;
		}
	}

	//Apply position
	m_pTransform->SetLocalPosition(pos);
}
