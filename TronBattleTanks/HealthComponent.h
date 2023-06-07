#pragma once
#include <memory>

#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class HealthComponent final : public BaseComponent
	{
	public:
		enum Events
		{
			damage = 0,
			heal,
			died
		};

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

		Subject<HealthComponent>* GetSubject() const;
		float GetHealth() const;
		float GetMaxHealth() const;

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;
	private:
		float m_currentHealth{1.f};
		float m_maxHealth{1.f};

		std::unique_ptr<Subject<HealthComponent>> m_subject = std::make_unique<Subject<HealthComponent>>();
	};
}
