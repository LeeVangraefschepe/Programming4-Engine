#include "ShootComponent.h"

#include <glm/vec2.hpp>

#include "AudioManager.h"
#include "Timer.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Transform.h"
#include "BulletComponent.h"
#include "ServiceLocator.h"

dae::ShootComponent::ShootComponent(GameObject* pGameObject, const glm::vec2* direction, float delay) : BaseComponent(pGameObject),
                                                                                                        m_direction(direction),
                                                                                                        m_maxDelay(delay)
{
	m_pTransform = pGameObject->GetComponent<Transform>();
}

void dae::ShootComponent::Update()
{
	m_currentDelay -= Time::GetDeltaTime();
}

void dae::ShootComponent::Shoot()
{
	if (m_currentDelay > 0.f) {return;}
	m_currentDelay = m_maxDelay;
	ServiceLocator::GetAudioSystem()->Play(AudioManager::Sounds::Fire, 1.f);
	const auto bullet = new GameObject{};
	const auto rootObject = SceneManager::GetInstance().GetActiveScene()->GetRootObject();
	bullet->SetParent(rootObject, false);
	constexpr glm::vec2 size{10.f,10.f};
	bullet->GetComponent<Transform>()->SetLocalPosition(m_pTransform->GetWorldPosition() + size);
	bullet->AddComponent<BulletComponent>(GetGameObject(), *m_direction, 300.f, 1.f);
}