#pragma once
#include "SpriteRenderer.h"
#include "Renderer.h"
#include "GameObject.h"
#include <iostream>

dae::SpriteRenderer::SpriteRenderer(GameObject* pGameObject, std::shared_ptr<Texture2D> pSprite)
	: m_pSprite(pSprite),
	RenderComponent(pGameObject)
{
	m_transform = m_pGameObject->GetComponent<Transform>();
}

void dae::SpriteRenderer::Render() const
{
	if (m_pSprite != nullptr)
	{
		if (m_transform.expired())
		{
			Renderer::GetInstance().RenderTexture(*m_pSprite, 0, 0);
			return;
		}
		const std::shared_ptr<Transform> transform = m_transform.lock();
		const auto& pos = transform->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pSprite, pos.x, pos.y);
	}
}