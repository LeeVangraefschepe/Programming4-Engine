#include "HealthComponent.h"
#include "EventQueue.h"
#include "GameObject.h"

dae::HealthComponent::HealthComponent(GameObject* pGameObject, float maxHealth) : BaseComponent(pGameObject)
{
	SetMaxHealth(maxHealth, true);
}
void dae::HealthComponent::SetHealth(float health)
{
	m_currentHealth = health;
}
void dae::HealthComponent::SetMaxHealth(float health, bool reset)
{
	m_maxHealth = health;
	if (reset)
	{
		ResetHealth();
	}
}
void dae::HealthComponent::ResetHealth()
{
	m_currentHealth = m_maxHealth;
}

void dae::HealthComponent::Heal(float amount)
{
	m_currentHealth += amount;
	if (m_currentHealth > m_maxHealth)
	{
		m_currentHealth = m_maxHealth;
	}
}
bool dae::HealthComponent::Damage(float amount)
{
	m_currentHealth -= amount;
	if (Died())
	{
		return true;
	}
	return false;
}
bool dae::HealthComponent::Died() const
{
	if (m_currentHealth <= 0.f)
	{
		EventQueue::GetInstance().SendMessage(Event{ "DIED" });
		GetGameObject()->GetSubject()->Notify(Event{ "DIED" }, GetGameObject());
		return true;
	}
	return false;
}