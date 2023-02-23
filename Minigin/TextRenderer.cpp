#pragma once
#include "TextRenderer.h"
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <stdexcept>
#include "GameObject.h"
#include "Renderer.h"

dae::TextRenderer::TextRenderer(GameObject* pGameObject, const std::string& text, std::shared_ptr<Font> font)
	: m_text(text), m_font(std::move(font)), m_textTexture(nullptr), RenderComponent(pGameObject)
{
	SetText(text);
	m_transform = m_pGameObject->GetComponent<Transform>();
}
void dae::TextRenderer::Render() const
{
	if (m_textTexture != nullptr)
	{
		if (m_transform.expired())
		{
			Renderer::GetInstance().RenderTexture(*m_textTexture, 0, 0);
		}
		else
		{
			const auto transform = m_transform.lock();
			const auto& pos = transform->GetPosition();
			Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
		}
	}
}

void dae::TextRenderer::UpdateTexture()
{
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
}