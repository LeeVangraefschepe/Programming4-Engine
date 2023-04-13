#include "HealthComponent.h"
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
	m_subject->Notify(Events::damage, this);
	if (Died())
	{
		m_subject->Notify(Events::died, this);
		return true;
	}
	return false;
}
bool dae::HealthComponent::Died()
{
	if (m_currentHealth <= 0.f)
	{
		ResetHealth();
		return true;
	}
	return false;
}

dae::Subject<dae::HealthComponent>* dae::HealthComponent::GetSubject() const
{
	return m_subject.get();
}

float dae::HealthComponent::GetHealth() const
{
	return m_currentHealth;
}

float dae::HealthComponent::GetMaxHealth() const
{
	return m_maxHealth;
}
