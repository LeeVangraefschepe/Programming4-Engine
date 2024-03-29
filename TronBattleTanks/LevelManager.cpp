#include "LevelManager.h"

#include <iostream>
#include <SDL_keycode.h>

#include "Commands.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "InputManager.h"
#include "LevelComponent.h"
#include "Transform.h"

dae::LevelManager::LevelManager(GameObject* pGameObject, LevelComponent* pLevel, const std::vector<GameObject*>& players, const std::vector<GameObject*>& enemies) : BaseComponent(pGameObject), m_pLevel(pLevel)
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

	const auto upAction = [this]()
	{
		m_nextGame = true;
	};
	m_pCommand = new LambdaCommand{ upAction };
	InputManager::GetInstance().BindCommand<LambdaCommand>(m_pCommand, SDLK_F1, InputManager::InputType::OnButtonDown);

	m_playerCount = static_cast<int>(players.size());
	m_alivePlayers = m_playerCount;

	m_enemyCount = static_cast<int>(enemies.size());
	m_aliveEnemies = m_enemyCount;
}

dae::LevelManager::~LevelManager()
{
	InputManager::GetInstance().RemoveCommand(m_pCommand);
}

void dae::LevelManager::StartGame()
{
	m_alivePlayers = m_playerCount;
	m_aliveEnemies = m_enemyCount;
	m_score = 0;
}

void dae::LevelManager::OnNotify(unsigned event, PlayerComponent* sender)
{
	const auto enumEvent = static_cast<PlayerComponent::Events>(event);
	if (enumEvent == PlayerComponent::died)
	{
		m_alivePlayers--;
	}
	else if (enumEvent == PlayerComponent::teleport)
	{
		std::cout << "Random pos\n";
		sender->GetTransform()->SetLocalPosition(m_pLevel->GetRandomSpawn());
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
	else if (m_aliveEnemies == 0 || m_nextGame)
	{
		ServiceLocator::GetGameState()->OnLevelCompleted();
		GameScene::Load();
	}
}