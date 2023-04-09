#include "PlayerComponent.h"
#include "GameObject.h"
#include "BasicEvents.h"
#include "EventQueue.h"

dae::PlayerComponent::PlayerComponent(GameObject* pGameObject) : BaseComponent(pGameObject)
{
	m_pHealthComponent = pGameObject->GetComponent<HealthComponent>();
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