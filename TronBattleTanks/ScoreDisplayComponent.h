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
		explicit ScoreDisplayComponent(GameObject* pGameObject, ScoreComponent* entity);
		~ScoreDisplayComponent() override;
		void OnNotify(unsigned eventId, ScoreComponent* entity) override;
		void OnDestroy() override;

		ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent(ScoreDisplayComponent&& other) = delete;
		ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) = delete;

	private:
		void SetDisplayScore(int amount) const;
		TextRenderer* m_pTextRenderer;

		ScoreComponent* m_pScoreComponent;
		bool m_isDestroyed{};
	};
}