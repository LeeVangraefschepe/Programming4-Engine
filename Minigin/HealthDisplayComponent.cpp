#include <sstream>

#include "HealthDisplayComponent.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "ResourceManager.h"
#include "TextRenderer.h"

dae::HealthDisplayComponent::HealthDisplayComponent(GameObject* pGameObject, const HealthComponent* entity) : BaseComponent(pGameObject)
{
	m_pTextRenderer = GetGameObject()->GetComponent<TextRenderer>();
	if (!m_pTextRenderer)
	{
		m_pTextRenderer = GetGameObject()->AddComponent<TextRenderer>("", ResourceManager::GetInstance().LoadFont("Lingua.otf", 24));
	}
	m_pTextRenderer->SetColor(255, 255, 255);
	entity->AddObservableObject(this);
	SetDisplayHealth(entity->GetHealth());
}

void dae::HealthDisplayComponent::OnNotify(unsigned, HealthComponent* entity)
{
	SetDisplayHealth(entity->GetHealth());
}

void dae::HealthDisplayComponent::SetDisplayHealth(float amount) const
{
	std::stringstream ss{};
	ss << "Health: " << amount;
	m_pTextRenderer->SetText(ss.str());
}
