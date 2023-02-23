#pragma once
#include "GameObject.h"

dae::GameObject::GameObject()
{
	AddComponent<Transform>();
}
dae::GameObject::~GameObject()
{
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