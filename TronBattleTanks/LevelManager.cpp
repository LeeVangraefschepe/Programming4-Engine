#include "LevelManager.h"

#include <iostream>

#include "GameObject.h"
#include "GameOverScene.h"

dae::LevelManager::LevelManager(GameObject* pGameObject, const std::vector<GameObject*>& players, const std::vector<GameObject*>& enemies) : BaseComponent(pGameObject)
{
	for (const auto player : players)
	{
		player->GetComponent<PlayerComponent>()->AddObservableObject(this);
		const auto score = player->GetComponent<ScoreComponent>();
		score->GetSubject()->AddObserver(this);
		m_scores.emplace_back(score);
	}

	for (const auto enemy : enemies)
	{
		enemy->GetComponent<HealthComponent>()->GetSubject()->AddObserver(this);
	}

	m_playerCount = static_cast<int>(players.size());
	m_alivePlayers = m_playerCount;

	m_enemyCount = static_cast<int>(enemies.size());
	m_aliveEnemies = m_enemyCount;
}

void dae::LevelManager::StartGame()
{
	m_alivePlayers = m_playerCount;
	m_aliveEnemies = m_enemyCount;
	m_score = 0;
}

void dae::LevelManager::OnNotify(unsigned event, PlayerComponent*)
{
	if (static_cast<PlayerComponent::Events>(event) == PlayerComponent::died)
	{
		m_alivePlayers--;
	}
}

void dae::LevelManager::OnNotify(unsigned event, HealthComponent*)
{
	if (static_cast<HealthComponent::Events>(event) == HealthComponent::died)
	{
		m_aliveEnemies--;
	}
}

void dae::LevelManager::OnNotify(unsigned amount, ScoreComponent*)
{
	m_score += static_cast<int>(amount);
	std::cout << "Total score: " << m_score << "\n";
}

void dae::LevelManager::Update()
{
	if (m_alivePlayers == 0)
	{
		GameOverScene::Load();
	}
	else if (m_aliveEnemies == 0)
	{
		std::cout << "Next level\n";
	}
}
