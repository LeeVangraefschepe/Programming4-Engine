#include "CollisionComponent.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "Transform.h"

dae::CollisionComponent::CollisionComponent(dae::GameObject* pGameObject) : BaseComponent(pGameObject)
{
	//Set default layer
	m_layers.push_back(0);

	m_transform = GetGameObject()->GetComponent<Transform>();
	PhysicsManager::GetInstance().AddCollider(this);
}

dae::CollisionComponent::CollisionComponent(dae::GameObject* pGameObject, std::vector<int> layers) : BaseComponent(pGameObject), m_layers(std::move(layers))
{
	m_transform = GetGameObject()->GetComponent<Transform>();
	PhysicsManager::GetInstance().AddCollider(this);
}

dae::CollisionComponent::~CollisionComponent()
{
	PhysicsManager::GetInstance().RemoveCollider(this);
}

void dae::CollisionComponent::SetSize(float width, float height)
{
	m_size.x = width;
	m_size.y = height;
}
