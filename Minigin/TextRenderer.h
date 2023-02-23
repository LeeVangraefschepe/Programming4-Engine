#pragma once
#include <memory>
#include <SDL_pixels.h>

#include "RenderComponent.h"
#include <string>
#include "Font.h"
#include "Texture2D.h"
#include "Transform.h"

namespace dae
{
	class TextRenderer : public RenderComponent
	{
	public:
		TextRenderer(GameObject* pGameObject, const std::string& text, std::shared_ptr<Font> font);
		~TextRenderer() override = default;

		void Render() const override;

		void SetText(const std::string& text) { m_text = text; UpdateTexture(); }
		void SetFont(std::shared_ptr<Font> font) { m_font = font; UpdateTexture(); }
		void SetColor(int r, int g, int b) { m_color = SDL_Color{ static_cast<uint8_t>(r),static_cast<uint8_t>(g),static_cast<uint8_t>(b) }; UpdateTexture(); }
		void SetColor(SDL_Color color) { m_color = color; UpdateTexture(); }

		TextRenderer(const TextRenderer& other) = delete;
		TextRenderer(TextRenderer&& other) = delete;
		TextRenderer& operator=(const TextRenderer& other) = delete;
		TextRenderer& operator=(TextRenderer&& other) = delete;
	private:

		void UpdateTexture();

		std::string m_text;
		std::weak_ptr<Transform> m_transform;
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
		SDL_Color m_color{255,255,255};
	};
}
