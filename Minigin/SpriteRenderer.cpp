#pragma once
#include "SpriteRenderer.h"
#include "Renderer.h"

#include <utility>
#include "GameObject.h"

dae::SpriteRenderer::SpriteRenderer(GameObject* pGameObject, std::shared_ptr<Texture2D> pSprite)
	: BaseComponent(pGameObject),
	  m_pSprite(std::move(pSprite))
{
	m_transform = GetGameObject()->GetComponent<Transform>();
	const auto size = m_pSprite->GetSize();
	m_size.x = static_cast<float>(size.x);
	m_size.y = static_cast<float>(size.y);
}

void dae::SpriteRenderer::Render()
{
	if (m_pSprite != nullptr)
	{
		if (m_transform == nullptr)
		{
			Renderer::GetInstance().RenderTexture(*m_pSprite, 0, 0);
			return;
		}
		const auto& pos = m_transform->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_pSprite, pos.x, pos.y);
	}
}

void dae::SpriteRenderer::SetSprite(const std::shared_ptr<Texture2D>& pSprite)
{
	m_pSprite = pSprite;
}

const glm::vec2& dae::SpriteRenderer::GetDimensions() const
{
	return m_size;
}
