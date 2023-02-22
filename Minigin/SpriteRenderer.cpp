#pragma once
#include "SpriteRenderer.h"
#include "Renderer.h"
#include "GameObject.h"

dae::SpriteRenderer::SpriteRenderer(GameObject* pGameObject, std::shared_ptr<Texture2D> pSprite)
	: m_pSprite(pSprite)
{
	m_pGameObject = pGameObject;
	m_transform = m_pGameObject->GetComponent<Transform>();
}

void dae::SpriteRenderer::Render()
{
	if (m_pSprite != nullptr)
	{
		if (m_transform != nullptr)
		{
			const auto& pos = m_transform->GetPosition();
			Renderer::GetInstance().RenderTexture(*m_pSprite, pos.x, pos.y);
		}
		else
		{
			Renderer::GetInstance().RenderTexture(*m_pSprite, 0, 0);
		}
		
	}
}

void dae::SpriteRenderer::SetPosition(float x, float y)
{
	m_transform->SetPosition(x, y, 0.0f);
}