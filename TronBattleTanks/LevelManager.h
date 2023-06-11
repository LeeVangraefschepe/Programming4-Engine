#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"

namespace dae
{
	class LevelManager : public BaseComponent, Observer<HealthComponent>, Observer<ScoreComponent>
	{
	public:
		explicit LevelManager(GameObject* pGameObject, const std::vector<GameObject*>& players);

		void StartGame();
		void OnNotify(unsigned, HealthComponent*) override;
		void OnNotify(unsigned, ScoreComponent*) override;

		void Update() override;

		LevelManager(const LevelManager& other) = delete;
		LevelManager(LevelManager&& other) = delete;
		LevelManager& operator=(const LevelManager& other) = delete;
		LevelManager& operator=(LevelManager&& other) = delete;
	private:
		int m_playerCount;
		int m_alivePlayers;

		std::vector<ScoreComponent*> m_scores{};
		int m_score{};
	};
}
