#pragma once
#include "GameObject.h"

dae::GameObject::~GameObject()
{
	for (const auto p : m_pComponents)
	{
		delete p;
	}	
}
void dae::GameObject::Update()
{
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

template<typename T>
void dae::GameObject::RemoveComponent() const
{
}