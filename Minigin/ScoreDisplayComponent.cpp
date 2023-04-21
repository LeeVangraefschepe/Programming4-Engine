#include <sstream>

#include "ScoreDisplayComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextRenderer.h"
#include "ScoreComponent.h"

dae::ScoreDisplayComponent::ScoreDisplayComponent(GameObject* pGameObject, ScoreComponent* entity) : BaseComponent(pGameObject), m_pScoreComponent(entity)
{
	m_pTextRenderer = GetGameObject()->GetComponent<TextRenderer>();
	if (!m_pTextRenderer)
	{
		m_pTextRenderer = GetGameObject()->AddComponent<TextRenderer>("", ResourceManager::GetInstance().LoadFont("Lingua.otf", 24));
	}
	m_pTextRenderer->SetColor(255, 255, 255);
	entity->GetSubject()->AddObserver(this);
	SetDisplayScore(entity->GetScore());
}

dae::ScoreDisplayComponent::~ScoreDisplayComponent()
{
	if (m_isDestroyed == false)
	{
		m_pScoreComponent->GetSubject()->RemoveObserver(this);
	}
}

void dae::ScoreDisplayComponent::OnNotify(unsigned, ScoreComponent* entity)
{
	SetDisplayScore(entity->GetScore());
}

void dae::ScoreDisplayComponent::OnDestroy()
{
	GetGameObject()->Destroy();
	m_isDestroyed = true;
}

void dae::ScoreDisplayComponent::SetDisplayScore(int amount) const
{
	std::stringstream ss{};
	ss << "Score: " << amount;
	m_pTextRenderer->SetText(ss.str());
}
