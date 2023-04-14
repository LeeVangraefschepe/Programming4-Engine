#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class ScoreComponent;
	class TextRenderer;

	class ScoreDisplayComponent : public BaseComponent, public Observer<ScoreComponent>
	{
	public:
		explicit ScoreDisplayComponent(GameObject* pGameObject, const ScoreComponent* entity);
		void OnNotify(unsigned eventId, ScoreComponent* entity) override;
		void OnDestroy() override;
	private:
		void SetDisplayScore(int amount) const;
		TextRenderer* m_pTextRenderer;
	};
}