#include "PlayerComponent.h"

#include <iostream>

#include "GameObject.h"
#include "BasicEvents.h"
#include "CollisionComponent.h"
#include "EventQueue.h"

#include "HealthComponent.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Time.h"

dae::PlayerComponent::PlayerComponent(GameObject* pGameObject) : BaseComponent(pGameObject)
{
	m_pTransform = pGameObject->GetComponent<Transform>();
	m_pHealthComponent = pGameObject->GetComponent<HealthComponent>();
	m_pSpriteRenderer = pGameObject->GetComponent<SpriteRenderer>();
	m_pCollision = pGameObject->GetComponent<CollisionComponent>();
}

void dae::PlayerComponent::Update()
{
	if (m_pCollision->IsColliding())
	{
		std::cout << "Collision working!\n";
	}
}

void dae::PlayerComponent::Damage(float value) const
{
	GetGameObject()->GetSubject()->Notify(static_cast<unsigned int>(BasicEvents::PlayerDamaged), GetGameObject());
	if (m_pHealthComponent->Damage(value))
	{
		GetGameObject()->GetSubject()->Notify(static_cast<unsigned int>(BasicEvents::PlayerDied), GetGameObject());
		EventQueue::GetInstance().SendMessage(static_cast<unsigned int>(BasicEvents::PlayerDied));
	}
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
}
