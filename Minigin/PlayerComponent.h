#pragma once
#include "BaseComponent.h"
#include "HealthComponent.h"

namespace dae
{
	class PlayerComponent final : public dae::BaseComponent
	{
	public:
		explicit PlayerComponent(GameObject* pGameObject);

		void Damage(float value) const;
	private:
		HealthComponent* m_pHealthComponent;
	};
}