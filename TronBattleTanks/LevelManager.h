#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "HealthComponent.h"
#include "PlayerComponent.h"
#include "ScoreComponent.h"

namespace dae
{
	class LevelComponent;
	class LambdaCommand;

	class LevelManager : public BaseComponent, Observer<PlayerComponent>, Observer<ScoreComponent>, Observer<HealthComponent>
	{
	public:
		explicit LevelManager(GameObject* pGameObject, LevelComponent* pLevel, const std::vector<GameObject*>& players, const std::vector<GameObject*>& enemies);
		~LevelManager() override;

		void StartGame();
		void OnNotify(unsigned, PlayerComponent*) override;
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

		int m_enemyCount;
		int m_aliveEnemies;
		bool m_nextGame{};

		LevelComponent* m_pLevel;
		LambdaCommand* m_pCommand;

		std::vector<ScoreComponent*> m_scores{};
		int m_score{};
	};
}
