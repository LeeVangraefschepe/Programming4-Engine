#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class HealthComponent;
	class TextRenderer;

	class HealthDisplayComponent : public BaseComponent, public Observer<HealthComponent>
	{
	public:
		explicit HealthDisplayComponent(GameObject* pGameObject, const HealthComponent* entity);
		void OnNotify(unsigned eventId, HealthComponent* entity) override;
		void OnDestroy() override;
	private:
		void SetDisplayHealth(float amount) const;
		TextRenderer* m_pTextRenderer;
	};
}
