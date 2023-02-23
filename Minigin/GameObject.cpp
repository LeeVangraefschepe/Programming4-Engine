#pragma once
#include "GameObject.h"
#include "ResourceManager.h"

dae::GameObject::GameObject()
{
	AddComponent<Transform>();
}
dae::GameObject::~GameObject()
{
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