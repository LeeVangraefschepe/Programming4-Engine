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

		void Render() const override;

		void SetText(const std::string& text);

		TextRenderer(const TextRenderer& other) = delete;
		TextRenderer(TextRenderer&& other) = delete;
		TextRenderer& operator=(const TextRenderer& other) = delete;
		TextRenderer& operator=(TextRenderer&& other) = delete;
	private:
		std::string m_text;
		std::weak_ptr<Transform> m_transform;
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
	};
}
