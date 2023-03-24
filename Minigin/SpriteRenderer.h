#pragma once
#include <memory>
#include "BaseComponent.h"
#include "Texture2D.h"
#include "Transform.h"

namespace dae
{
	class SpriteRenderer final : public BaseComponent
	{
	public:
		SpriteRenderer(GameObject* pGameObject ,std::shared_ptr<Texture2D> pSprite);
		~SpriteRenderer() override = default;

		void Render() override;
		void SetSprite(const std::shared_ptr<Texture2D>& pSprite);
		const glm::vec2& GetDimensions() const;

		SpriteRenderer(const SpriteRenderer& other) = delete;
		SpriteRenderer(SpriteRenderer&& other) = delete;
		SpriteRenderer& operator=(const SpriteRenderer& other) = delete;
		SpriteRenderer& operator=(SpriteRenderer&& other) = delete;
	private:
		Transform* m_transform{};
		glm::vec2 m_size{};
		std::shared_ptr<Texture2D> m_pSprite;
	};
}