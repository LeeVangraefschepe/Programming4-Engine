#include "ScoreComponent.h"
#include "ScoreManager.h"

dae::ScoreComponent::ScoreComponent(GameObject* pGameObject) : BaseComponent(pGameObject)
{

}

int dae::ScoreComponent::GetScore() const
{
	return m_score;
}

void dae::ScoreComponent::AddScore(int amount)
{
	if (amount == 0) return;
	m_score += amount;
	ScoreManager::GetInstance().AddScore(amount);
	m_subject->Notify(amount, this);
}

void dae::ScoreComponent::ResetScore()
{
	m_score = 0;
	m_subject->Notify(0, this);
}