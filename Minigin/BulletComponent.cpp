#include "BulletComponent.h"

#include "CollisionComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "Time.h"

dae::BulletComponent::BulletComponent(GameObject* pGameObject, GameObject* pCreator, const glm::vec2& direcion, float speed, float damage) :
BaseComponent(pGameObject),
m_pCreator(pCreator),
m_direction(direcion),
m_speed(speed),
m_damage(damage)
{
	m_pTransform = GetGameObject()->GetComponent<Transform>();
	m_pCollision = GetGameObject()->GetComponent<CollisionComponent>();
}

void dae::BulletComponent::Update()
{
	if (const auto other = m_pCollision->IsColliding(); other && other != m_pCreator)
	{
		if (const auto otherHealth = other->GetComponent<HealthComponent>())
		{
			const auto scoreCreator = m_pCreator->GetComponent<ScoreComponent>();
			const bool kill = otherHealth->Damage(m_damage);
			if (scoreCreator)
			{
				scoreCreator->AddScore(100 + (kill * 500));
			}
		}
		GetGameObject()->SetParent(nullptr, false);

		return;
	}

	auto pos = m_pTransform->GetLocalPosition();
	pos += m_direction * Time::GetDeltaTime() * m_speed;
	m_pTransform->SetLocalPosition(pos);
}