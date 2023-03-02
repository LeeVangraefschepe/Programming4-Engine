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
	if (IsValidParent(parent) == false)
	{
		return;
	}

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
			transform->SetLocalPosition(transform->GetLocalPosition() - m_pParent.lock()->GetComponent<Transform>().lock()->GetWorldPosition());
		}
		transform->SetPositionDirty();
	}
}
void dae::GameObject::AddChild(std::weak_ptr<GameObject> child)
{
	m_pChildren.push_back(child);
}
void dae::GameObject::RemoveChild(std::weak_ptr<GameObject> child)
{
	for (auto it = m_pChildren.begin(); it != m_pChildren.end(); ++it) {
		std::weak_ptr pChild{ *it };
		if (pChild.lock() == child.lock()) {
			pChild.lock()->SetParent(std::weak_ptr<GameObject>{}, true);
			m_pChildren.erase(it);
			return;
		}
	}
}
bool dae::GameObject::IsValidParent(std::weak_ptr<GameObject> parent)
{
	const auto sParent = parent.lock();
	const auto thischild = weak_from_this().lock();

	//Nullptr
	if (m_pParent.expired())
	{
		return true;
	}

	//Parent equals himself
	if (sParent == thischild)
	{
		return false;
	}

	//Check if already child
	const auto parentChildren = sParent->GetChildren();
	for (const auto child : parentChildren)
	{
		if (child.lock() == thischild)
		{
			return  false;
		}
	}

	return true;
}
