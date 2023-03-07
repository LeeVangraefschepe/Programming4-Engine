#pragma once
#include "GameObject.h"

#include <algorithm>

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
	if (m_pDestroyComponents.empty() == false)
	{
		for (auto it = m_pDestroyComponents.begin(); it != m_pDestroyComponents.end(); ++it)
		{
			EraseComponent(it->lock());
		}
		m_pDestroyComponents.clear();
	}
	for (const auto p : m_pComponents)
	{
		p->Update();
	}
}
void dae::GameObject::Render() const
{
	for (const auto p : m_pComponents)
	{
		p->Render();
	}
}
void dae::GameObject::SetParent(std::weak_ptr<GameObject> parent, bool keepWorldPosition)
{
	if (IsValidParent(parent) == false)
	{
		//todo: add throw for user of the engine?
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
			//pChild.lock()->SetParent(std::weak_ptr<GameObject>{}, true);
			m_pChildren.erase(it);
			return;
		}
	}
}
bool dae::GameObject::HasChild(std::shared_ptr<GameObject> child) const
{
	for (const auto element : m_pChildren)
	{
		const auto sElement = element.lock();
		if (sElement == child)
		{
			return true;
		}
		if (sElement->HasChild(child))
		{
			return true;
		}
	}
	return false;
}
void dae::GameObject::EraseComponent(const std::shared_ptr<BaseComponent> component)
{
	for (auto it = m_pComponents.begin(); it != m_pComponents.end(); ++it)
	{
		if (component == *it)
		{
			m_pComponents.erase(it);
			break;
		}
	}
}
bool dae::GameObject::IsValidParent(std::weak_ptr<GameObject> parent)
{
	//Nullptr is valid
	if (parent.expired())
	{
		return true;
	}

	const auto sParent = parent.lock();
	const auto thischild = weak_from_this().lock();

	//Parent equals himself
	if (sParent == thischild)
	{
		return false;
	}

	//todo: replace fors with stl
	//return std::ranges::any_of(parentChildren, [&thischild](const std::weak_ptr<GameObject> child) {return child.lock() == thischild; });

	//Check if already child
	const auto parentChildren = sParent->GetChildren();
	for (const auto child : parentChildren)
	{
		if (child.lock() == thischild)
		{
			return false;
		}
	}

	//Check if this is one of your childs
	if (HasChild(sParent))
	{
		return false;
	}
	
	return true;
}