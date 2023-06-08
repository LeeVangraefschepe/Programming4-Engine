#include "BulletComponent.h"

#include "CellComponent.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "HealthComponent.h"
#include "PhysicsManager.h"
#include "ResourceManager.h"
#include "ScoreComponent.h"
#include "SpriteRenderer.h"
#include "Timer.h"

dae::BulletComponent::BulletComponent(GameObject* pGameObject, GameObject* pCreator, const glm::vec2& direction, float speed, float damage) :
BaseComponent(pGameObject),
m_pCreator(pCreator),
m_direction(direction),
m_speed(speed),
m_damage(damage)
{
	const std::vector layers{1};
	const glm::vec2 size = pGameObject->AddComponent<SpriteRenderer>(ResourceManager::GetInstance().LoadTexture("BulletPlayer.png"))->GetDimensions();
	m_pCollision = pGameObject->AddComponent<CollisionComponent>(layers);
	m_pTransform = BaseComponent::GetGameObject()->GetComponent<Transform>();
	m_pCollision->SetSize(size.x, size.y);
}

void dae::BulletComponent::Update()
{
	const float deltaTime = Time::GetDeltaTime();
	m_timeAlive += deltaTime;
	if (m_maxTimeAlive <= m_timeAlive)
	{
		GetGameObject()->Destroy();
		return;
	}

	auto& physics = PhysicsManager::GetInstance();
	if (const auto other = physics.CheckCollision(m_pCollision); other && other != m_pCreator)
	{
		++m_bounces;
		if (const auto otherHealth = other->GetComponent<HealthComponent>())
		{
			const auto scoreCreator = m_pCreator->GetComponent<ScoreComponent>();
			const bool kill = otherHealth->Damage(m_damage);
			if (scoreCreator)
			{
				scoreCreator->AddScore(100 + (kill * 500));
			}
			GetGameObject()->Destroy();
		}

		m_direction *= -1.f;
		auto pos = m_pTransform->GetLocalPosition();
		pos += m_direction * 5.f;
		m_pTransform->SetLocalPosition(pos);

		return;
	}

	if (m_bounces >= m_maxBounces)
	{
		GetGameObject()->Destroy();
	}

	auto pos = m_pTransform->GetLocalPosition();
	pos += m_direction * deltaTime * m_speed;
	m_pTransform->SetLocalPosition(pos);
}