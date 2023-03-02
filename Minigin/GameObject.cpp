#pragma once
#include "GameObject.h"
#include "ResourceManager.h"

dae::GameObject::GameObject()
{
	AddComponent<Transform>();
}
dae::GameObject::~GameObject()
{
	for (auto child : m_pChildren)
	{
		child.lock()->SetParent(std::weak_ptr<GameObject>{}, true);
	}
}
void dae::GameObject::Update()
{
	for (const auto p : m_pUpdateComponents)
	{
		p->Update();
	}
}
void dae::GameObject::Render() const
{
	for (const auto p : m_pRenderComponents)
	{
		p->Render();
	}
}
void dae::GameObject::SetParent(std::weak_ptr<GameObject> parent, bool keepWorldPosition)
{
	if (m_pParent.expired() == false)
	{
		m_pParent.lock()->RemoveChild(weak_from_this());
	}
	m_pParent = parent;
	const auto wTransform = GetComponent<Transform>();
	if (wTransform.expired())
	{
		return;
	}
	const auto transform = wTransform.lock();
	if (m_pParent.expired())
	{
		transform->SetLocalPosition(transform->GetWorldPosition());
	}
	else
	{
		m_pParent.lock()->AddChild(weak_from_this());
		if (keepWorldPosition)
		{
			transform->SetLocalPosition(transform->GetPosition() - m_pParent.lock()->GetComponent<Transform>().lock()->GetWorldPosition());
		}
		transform->SetPositionDirty();
	}
}