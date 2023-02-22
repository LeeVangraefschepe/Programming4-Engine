#pragma once
#include <memory>
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

		void Update() override;
		void Render() override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

		TextRenderer(const TextRenderer& other) = delete;
		TextRenderer(TextRenderer&& other) = delete;
		TextRenderer& operator=(const TextRenderer& other) = delete;
		TextRenderer& operator=(TextRenderer&& other) = delete;
	private:
		bool m_needsUpdate;
		std::string m_text;
		Transform m_transform{};
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
	};
}
