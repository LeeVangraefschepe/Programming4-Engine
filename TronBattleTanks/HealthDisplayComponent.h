#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class HealthComponent;
	class TextRenderer;

	class HealthDisplayComponent final : public BaseComponent, public Observer<HealthComponent>
	{
	public:
		explicit HealthDisplayComponent(GameObject* pGameObject, HealthComponent* entity);
		~HealthDisplayComponent() override;
		void OnNotify(unsigned eventId, HealthComponent* entity) override;
		void OnDestroy() override;

		HealthDisplayComponent(const HealthDisplayComponent& other) = delete;
		HealthDisplayComponent(HealthDisplayComponent&& other) = delete;
		HealthDisplayComponent& operator=(const HealthDisplayComponent& other) = delete;
		HealthDisplayComponent& operator=(HealthDisplayComponent&& other) = delete;
	private:
		void SetDisplayHealth(float amount) const;
		TextRenderer* m_pTextRenderer;


		HealthComponent* m_pHealthComponent;
		bool m_isDestroyed{};
	};
}
