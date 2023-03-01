#pragma once
#include <memory>
#include "RenderComponent.h"
#include <string>
#include "Font.h"
#include "Texture2D.h"
#include "Transform.h"

namespace dae
{
	class SpriteRenderer : public RenderComponent
	{
	public:
		SpriteRenderer(GameObject* pGameObject ,std::shared_ptr<Texture2D> pSprite);
		~SpriteRenderer() override = default;

		void Render() const override;
		void SetSprite(std::shared_ptr<Texture2D> pSprite);

		SpriteRenderer(const SpriteRenderer& other) = delete;
		SpriteRenderer(SpriteRenderer&& other) = delete;
		SpriteRenderer& operator=(const SpriteRenderer& other) = delete;
		SpriteRenderer& operator=(SpriteRenderer&& other) = delete;
	private:
		std::weak_ptr<Transform> m_transform{};
		std::shared_ptr<Texture2D> m_pSprite;
	};
}