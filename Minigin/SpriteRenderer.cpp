#pragma once
#include "SpriteRenderer.h"
#include "Renderer.h"
#include "GameObject.h"

dae::SpriteRenderer::SpriteRenderer(GameObject* pGameObject, std::shared_ptr<Texture2D> pSprite)
	: m_pSprite(pSprite),
	BaseComponent(pGameObject)
{
	m_transform = GetGameObject()->GetComponent<Transform>();
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
		const auto& pos = transform->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_pSprite, pos.x, pos.y);
	}
}

void dae::SpriteRenderer::SetSprite(const std::shared_ptr<Texture2D> pSprite)
{
	m_pSprite = pSprite;
}