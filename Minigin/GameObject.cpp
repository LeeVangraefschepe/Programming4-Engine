#pragma once
#include <algorithm>
#include "GameObject.h"
#include "Transform.h"

dae::GameObject::GameObject()
{
	AddComponent<Transform>();
}
dae::GameObject::~GameObject()
{
	int i{};
	++i;
}
void dae::GameObject::Update()
{
	if (m_pDestroyComponents.empty() == false)
	{
		for (const auto& destroyComponent : m_pDestroyComponents)
		{
			EraseComponent(destroyComponent);
		}
		m_pDestroyComponents.clear();
	}
	if (m_pDeletedChildren.empty() == false)
	{
		for (const auto& deletedChild : m_pDeletedChildren)
		{
			EraseChild(deletedChild);
		}
		m_pDeletedChildren.clear();
	}

	for (const auto& p : m_pComponents)
	{
		p->Update();
	}
	for (const auto& child : m_pChildren)
	{
		child->Update();
	}
}
void dae::GameObject::Render() const
{
	for (const auto& p : m_pComponents)
	{
		p->Render();
	}
	for (const auto& child : m_pChildren)
	{
		child->Render();
	}
}
void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (!IsValidParent(parent)){return;}

	auto transform = GetComponent<Transform>();
	if (parent == nullptr)
	{
		transform->SetLocalPosition(transform->GetWorldPosition());
	}
	else
	{
		if (keepWorldPosition)
		{
			transform->SetPosition(transform->GetWorldPosition() - m_pParent->GetComponent<Transform>()->GetWorldPosition());
			transform->SetPositionDirty();
		}
	}

	std::unique_ptr<GameObject> child;
	if (m_pParent != nullptr)
	{
		for (auto it = m_pParent->m_pChildren.begin(); it != m_pParent->m_pChildren.end(); ++it)
			if (it->get() == this)
			{
				if (parent == nullptr)
				{
					m_pParent->m_pDeletedChildren.push_back(this);
					return;
				}
				child = std::move(*it);
				break;
			}
		
	}

	m_pParent = parent;
	if (m_pParent != nullptr)
	{
		if (child == nullptr)
		{
			child = std::unique_ptr<GameObject>(this);
			m_pParent->m_pChildren.emplace_back(std::move(child));
		}
	}
}
bool dae::GameObject::HasChild(GameObject* child) const
{
	for (const auto& element : m_pChildren)
	{
		const auto rawElement = element.get();
		if (rawElement == child)
		{
			return true;
		}
		if (rawElement->HasChild(child))
		{
			return true;
		}
	}
	return false;
}
void dae::GameObject::EraseComponent(const BaseComponent* component)
{
	for (auto it = m_pComponents.begin(); it != m_pComponents.end(); ++it)
	{
		if (component == it->get())
		{
			m_pComponents.erase(it);
			break;
		}
	}
}

void dae::GameObject::EraseChild(const GameObject* gameobject)
{
	for (auto it = m_pChildren.begin(); it != m_pChildren.end(); ++it)
	{
		if (gameobject == it->get())
		{
			m_pChildren.erase(it);
			break;
		}
	}
}

bool dae::GameObject::IsValidParent(GameObject* parent) const
{
	//Nullptr is valid
	if (parent == nullptr)
	{
		return true;
	}

	//Parent equals himself
	if (parent == this)
	{
		return false;
	}

	//todo: replace fors with stl
	//return std::ranges::any_of(parentChildren, [&thischild](const std::weak_ptr<GameObject> child) {return child.lock() == thischild; });

	//Check if already child
	const auto parentChildren = parent->GetChildren();
	for (const auto child : parentChildren)
	{
		if (child == this)
		{
			return false;
		}
	}

	//Check if this is one of your childs
	if (HasChild(parent))
	{
		return false;
	}
	
	return true;
}
