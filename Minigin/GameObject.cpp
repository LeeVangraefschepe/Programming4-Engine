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

	if (m_texture == nullptr)
	{
		return;
	}
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
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
