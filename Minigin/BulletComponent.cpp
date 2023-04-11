#include "BulletComponent.h"

#include "CollisionComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "HealthComponent.h"
#include "Time.h"

dae::BulletComponent::BulletComponent(GameObject* pGameObject, GameObject* pIgnore, const glm::vec2& direcion, float speed, float damage) :
BaseComponent(pGameObject),
m_pIgnore(pIgnore),
m_direction(direcion),
m_speed(speed),
m_damage(damage)
{
	m_pTransform = GetGameObject()->GetComponent<Transform>();
	m_pCollision = GetGameObject()->GetComponent<CollisionComponent>();
}

void dae::BulletComponent::Update()
{
	auto other = m_pCollision->IsColliding();
	if (other && other != m_pIgnore)
	{
		auto otherHealth = other->GetComponent<HealthComponent>();
		if (otherHealth)
		{
			otherHealth->Damage(1.f);
		}
		GetGameObject()->SetParent(nullptr, false);
		return;
	}

	auto pos = m_pTransform->GetLocalPosition();
	pos += m_direction * Time::GetDeltaTime() * m_speed;
	m_pTransform->SetLocalPosition(pos);
}