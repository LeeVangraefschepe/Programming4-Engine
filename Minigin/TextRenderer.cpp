#pragma once
#include "TextRenderer.h"
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <stdexcept>
#include "GameObject.h"
#include "Renderer.h"

dae::TextRenderer::TextRenderer(GameObject* pGameObject, const std::string& text, std::shared_ptr<Font> font)
	: m_text(text), m_font(std::move(font)), m_textTexture(nullptr), BaseComponent(pGameObject)
{
	SetText(text);
	m_transform = GetGameObject()->GetComponent<Transform>();
	m_spriteRenderer = GetGameObject()->GetComponent<SpriteRenderer>();
	if (m_spriteRenderer == nullptr)
	{
		m_spriteRenderer = GetGameObject()->AddComponent<SpriteRenderer>(m_textTexture);
	}
}
void dae::TextRenderer::Update()
{
	if (m_needsUpdate)
	{
		UpdateTexture();
		m_spriteRenderer->SetSprite(m_textTexture);
		m_needsUpdate = false;
	}
}

void dae::TextRenderer::UpdateTexture()
{
	m_needsUpdate = true;
	const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_textTexture = std::make_shared<Texture2D>(texture);

	const auto size = m_textTexture->GetSize();
	m_size.x = static_cast<float>(size.x);
	m_size.y = static_cast<float>(size.y);
}