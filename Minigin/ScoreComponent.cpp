#include "ScoreComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* pGameObject) : BaseComponent(pGameObject)
{

}

void dae::ScoreComponent::AddObservableObject(Observer<ScoreComponent>* observer) const
{
	m_subject->AddObserver(observer);
}

int dae::ScoreComponent::GetScore() const
{
	return m_score;
}

void dae::ScoreComponent::AddScore(int amount)
{
	m_score += amount;
	m_subject->Notify(0, this);
}

void dae::ScoreComponent::ResetScore()
{
	m_score = 0;
	m_subject->Notify(0, this);
}
