#include "GameState.h"

void GameState::OnLevelStarted()
{
	m_currentLevel = 0;
}

void GameState::OnLevelCompleted()
{
	++m_currentLevel;
	if (m_currentLevel > m_lastLevel)
	{
		
	}
}

bool GameState::GetLevelId(int& id) const
{
	if (m_currentLevel > m_lastLevel)
	{
		return true;
	}

	id = m_currentLevel;
	return false;
}
