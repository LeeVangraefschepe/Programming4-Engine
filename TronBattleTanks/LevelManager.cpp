#include "LevelManager.h"

#include <iostream>

#include "GameObject.h"
#include "GameOverScene.h"

dae::LevelManager::LevelManager(GameObject* pGameObject, const std::vector<GameObject*>& players) : BaseComponent(pGameObject)
{
	for (const auto player : players)
	{
		player->GetComponent<HealthComponent>()->GetSubject()->AddObserver(this);
		const auto score = player->GetComponent<ScoreComponent>();
		score->GetSubject()->AddObserver(this);
		m_scores.emplace_back(score);
	}
	m_playerCount = static_cast<int>(players.size());
	m_alivePlayers = m_playerCount;
}

void dae::LevelManager::StartGame()
{
	m_alivePlayers = m_playerCount;
	m_score = 0;
}

void dae::LevelManager::OnNotify(unsigned event, HealthComponent*)
{
	if (static_cast<HealthComponent::Events>(event) == HealthComponent::died)
	{
		m_alivePlayers--;
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
}
