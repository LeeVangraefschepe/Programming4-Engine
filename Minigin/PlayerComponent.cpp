#include "PlayerComponent.h"

#include <iostream>

#include "GameObject.h"
#include "BasicEvents.h"
#include "BulletComponent.h"
#include "CollisionComponent.h"
#include "EventQueue.h"
#include "HealthComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "ScoreComponent.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Time.h"

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
	//Update player UI
	if (abs(input.x) >= abs(input.y))
	{
		if (input.x >= 0)
		{
			m_direction = 2; // right
		}
		else
		{
			m_direction = 0; // left
		}
	}
	else
	{
		if (input.y >= 0)
		{
			m_direction = 1; // top
		}
		else
		{
			m_direction = 3; // bottom
		}
	}
	m_pSpriteRenderer->SetRotation(static_cast<float>(m_direction) * 90.f);

	//Move the player
	input.y *= -1.f;
	input *= Time::GetDeltaTime() * 100.f;

	auto pos = m_pTransform->GetLocalPosition();
	pos += input;
	m_pTransform->SetLocalPosition(pos);
}

void dae::PlayerComponent::FireInput()
{
	std::cout << "Fire bullet\n";
	const auto bullet = new GameObject{};
	bullet->SetParent(m_pRootObject, false);
	bullet->GetComponent<Transform>()->SetLocalPosition(m_pTransform->GetWorldPosition());
	const auto size = bullet->AddComponent<SpriteRenderer>(ResourceManager::GetInstance().LoadTexture("BulletPlayer.png"))->GetDimensions();
	bullet->AddComponent<CollisionComponent>()->SetSize(size.x, size.y);
	bullet->AddComponent<BulletComponent>(GetGameObject(), DIRECTIONS[m_direction], 300.f, 1.f);
}

void dae::PlayerComponent::OnNotify(unsigned eventId, HealthComponent*)
{
	m_subject->Notify(Events::damage, this);
	if (eventId == HealthComponent::Events::died)
	{
		m_subject->Notify(Events::died, this);
		EventQueue::GetInstance().SendMessage(static_cast<unsigned int>(BasicEvents::PlayerDied));
		GetGameObject()->Destroy();
	}
}
void dae::PlayerComponent::OnNotify(unsigned, ScoreComponent*)
{
	m_subject->Notify(Events::score, this);
	EventQueue::GetInstance().SendMessage(static_cast<unsigned int>(BasicEvents::PlayerScore));
}

dae::PlayerComponent::PlayerData* dae::PlayerComponent::GetData() const
{
	return m_pData.get();
}
