#pragma once
#include <memory>
#include <SDL_pixels.h>

#include <string>
#include "Font.h"
#include "SpriteRenderer.h"
#include "Texture2D.h"
#include "Transform.h"

namespace dae
{
	class TextRenderer final : public BaseComponent
	{
	public:
		TextRenderer(GameObject* pGameObject, const std::string& text, std::shared_ptr<Font> font);
		~TextRenderer() override = default;

		void Update() override;

		void SetText(const std::string& text) { m_text = text; UpdateTexture(); }
		void SetFont(std::shared_ptr<Font> font) { m_font = font; UpdateTexture(); }
		void SetColor(int r, int g, int b) { m_color = SDL_Color{ static_cast<uint8_t>(r),static_cast<uint8_t>(g),static_cast<uint8_t>(b) }; UpdateTexture(); }
		void SetColor(SDL_Color color) { m_color = color; UpdateTexture(); }

		const glm::vec2& GetDimensions() const { return m_size; }

		TextRenderer(const TextRenderer& other) = delete;
		TextRenderer(TextRenderer&& other) = delete;
		TextRenderer& operator=(const TextRenderer& other) = delete;
		TextRenderer& operator=(TextRenderer&& other) = delete;
	private:

		void UpdateTexture();

		std::string m_text;
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
		SDL_Color m_color{255,255,255};
		glm::vec2 m_size;

		//Other components
		Transform* m_transform;
		SpriteRenderer* m_spriteRenderer;

		//Dirty flag
		bool m_needsUpdate{ true };
	};
}
