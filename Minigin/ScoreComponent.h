#pragma once
#include <memory>
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class ScoreComponent final : public BaseComponent
	{
	public:
		explicit ScoreComponent(GameObject* pGameObject);
		Subject<ScoreComponent>* GetSubject() const { return m_subject.get(); }

		int GetScore() const;

		void AddScore(int amount);
		void ResetScore();
	private:
		std::unique_ptr<Subject<ScoreComponent>> m_subject = std::make_unique<Subject<ScoreComponent>>();
		int m_score{};
	};
}