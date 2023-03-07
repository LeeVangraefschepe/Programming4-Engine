#pragma once
#include "TextRenderer.h"

namespace dae
{
	class FPS final : public BaseComponent
	{
	public:
		explicit FPS(GameObject* pGameObject, float updateInterval = 1.f);

		~FPS() override;
		void Update() override;
	private:
		std::weak_ptr<TextRenderer> m_pTextRenderer;
		float m_timeTillUpdate{ 0.f };
		float m_timeInterval;
	};
}
