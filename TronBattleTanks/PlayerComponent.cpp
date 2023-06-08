#include "PlayerComponent.h"

#include <iostream>

#include "AudioManager.h"
#include "GameObject.h"
#include "BulletComponent.h"
#include "CollisionComponent.h"
#include "EventQueue.h"
#include "HealthComponent.h"
#include "PhysicsManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "ScoreComponent.h"
#include "ServiceLocator.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Timer.h"
#include "CellComponent.h"

dae::PlayerComponent::PlayerComponent(GameObject* pGameObject) : BaseComponent(pGameObject)
{
	m_pData->healthComponent = pGameObject->GetComponent<HealthComponent>();
	m_pData->scoreComponent = pGameObject->GetComponent<ScoreComponent>();
	m_pData->healthComponent->GetSubject()->AddObserver(this);
	m_pData->scoreComponent->GetSubject()->AddObserver(this);

	m_pTransform = pGameObject->GetComponent<Transform>();
	m_pSpriteRenderer = pGameObject->GetComponent<SpriteRenderer>();
	m_pCollision = pGameObject->GetComponent<CollisionComponent>();

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

void dae::PlayerComponent::FireInput()
{
	ServiceLocator::GetAudioSystem()->Play(AudioManager::Sounds::Fire, 1.f);
	std::cout << "Fire bullet\n";
	const auto bullet = new GameObject{};
	bullet->SetParent(m_pRootObject, false);
	bullet->GetComponent<Transform>()->SetLocalPosition(m_pTransform->GetWorldPosition());
	bullet->AddComponent<BulletComponent>(GetGameObject(), m_direction, 300.f, 1.f);
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

void dae::PlayerComponent::HandleMovement(glm::vec2 input) const
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
	}

	//Apply position
	m_pTransform->SetLocalPosition(pos);
}
