#pragma once
#include "BaseComponent.h"

namespace dae
{
	class HealthComponent final : public dae::BaseComponent
	{
	public:
		explicit HealthComponent(GameObject* pGameObject, float maxHealth);

		void SetHealth(float health);
		void SetMaxHealth(float health, bool reset = true);
		void ResetHealth();
		void Heal(float amount);

		/**
		 * \return If the health is under zero it returns zero. 
		 */
		bool Damage(float amount);
		bool Died();

	private:
		float m_currentHealth{1.f};
		float m_maxHealth{1.f};
	};
}