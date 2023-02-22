#pragma once
#include "TextRenderer.h"
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <stdexcept>
#include "GameObject.h"
#include "Renderer.h"

dae::TextRenderer::TextRenderer(GameObject* pGameObject, const std::string& text, std::shared_ptr<Font> font)
	: m_needsUpdate(true), m_text(text), m_font(std::move(font)), m_textTexture(nullptr), RenderComponent(pGameObject)
{
	m_transform = m_pGameObject->GetComponent<Transform>();
}
void dae::TextRenderer::Update()
{
	if (m_needsUpdate)
	{
		constexpr SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
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
		m_needsUpdate = false;
	}
}
void dae::TextRenderer::Render()
{
	if (m_textTexture != nullptr)
	{
		if (m_transform != nullptr)
		{
			const auto& pos = m_transform->GetPosition();
			Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
		}
		else
		{
			Renderer::GetInstance().RenderTexture(*m_textTexture, 0, 0);
		}
	}
}
void dae::TextRenderer::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}