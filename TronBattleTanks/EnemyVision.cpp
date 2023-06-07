#include "EnemyVision.h"

#include "CellComponent.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "PlayerComponent.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

dae::EnemyVision::EnemyVision(GameObject* pGameObject, CollisionComponent* ignore, int* direction) : BaseComponent(pGameObject)
{
	m_pIgnore.emplace_back(ignore);
	m_direction = direction;

	constexpr float visionLength = 50.f;
	constexpr float visionWidth = 5.f;

	//Left
	auto child = new GameObject{};
	DIRECTIONS[0] = child->AddComponent<CollisionComponent>();
	DIRECTIONS[0]->SetSize(visionLength, visionWidth);
	child->SetParent(pGameObject, false);
	child->GetComponent<Transform>()->SetLocalPosition(-visionLength, 0.f);

	//Top
	child = new GameObject{};
	DIRECTIONS[3] = child->AddComponent<CollisionComponent>();
	DIRECTIONS[3]->SetSize(visionWidth, visionLength);
	child->SetParent(pGameObject, false);
	child->GetComponent<Transform>()->SetLocalPosition(0.f, -visionLength);
	//child->AddComponent<SpriteRenderer>(ResourceManager::GetInstance().LoadTexture("Debug.png"));

	//Right
	child = new GameObject{};
	DIRECTIONS[2] = child->AddComponent<CollisionComponent>();
	DIRECTIONS[2]->SetSize(visionLength, visionWidth);
	child->SetParent(pGameObject, false);

	//Bottom
	child = new GameObject{};
	DIRECTIONS[1] = child->AddComponent<CollisionComponent>();
	DIRECTIONS[1]->SetSize(visionWidth, visionLength);
	child->SetParent(pGameObject, false);

	//Add direction tests to ignore
	for (int i{}; i < 4; ++i)
	{
		m_pIgnore.emplace_back(DIRECTIONS[i]);
	}
}

void dae::EnemyVision::Update()
{
	if (const auto other = PhysicsManager::GetInstance().CheckCollisonClosest(DIRECTIONS[*m_direction], m_pIgnore); other)
	{
		if (other->HasComponent<PlayerComponent>())
		{
			m_subject->Notify(Fire, this);
		}
	}
}
