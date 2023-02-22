#pragma once
#include "SpriteRenderer.h"
#include "Renderer.h"

dae::SpriteRenderer::SpriteRenderer(std::shared_ptr<Texture2D> pSprite)
	: m_needsUpdate(true), m_pSprite(pSprite)
{
}

void dae::SpriteRenderer::Render()
{
	if (m_pSprite != nullptr)
	{
		const auto& pos = m_transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pSprite, pos.x, pos.y);
	}
}

void dae::SpriteRenderer::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}