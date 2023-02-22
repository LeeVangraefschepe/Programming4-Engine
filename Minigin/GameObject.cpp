#pragma once
#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

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
T* dae::GameObject::GetComponent() const
{
	return nullptr;
}
template<typename T>
void dae::GameObject::RemoveComponent() const
{

}