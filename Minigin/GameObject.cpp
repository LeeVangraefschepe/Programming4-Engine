#pragma once
#include "GameObject.h"

dae::GameObject::GameObject()
{
	m_pComponents.push_back(new Transform{this});
}
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