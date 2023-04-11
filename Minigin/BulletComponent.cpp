#include "BulletComponent.h"

#include "Scene.h"
#include "SceneManager.h"

dae::BulletComponent::BulletComponent(GameObject* pGameObject, const glm::vec2& direcion, float speed) :
BaseComponent(pGameObject),
m_direction(direcion),
m_speed(speed)
{
	m_rootObject = SceneManager::GetInstance().GetActiveScene()->GetRootObject();
}

void dae::BulletComponent::Update()
{
	auto oteherObjects = m_rootObject->GetChildren();
	const auto self = GetGameObject();
	for (auto& other : oteherObjects)
	{
		if (other == self) continue;
	}
}
