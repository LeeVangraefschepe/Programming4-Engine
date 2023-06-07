#pragma once
#include "BaseComponent.h"
#include "TextRenderer.h"

namespace dae
{
	class FPS final : public BaseComponent
	{
	public:
		explicit FPS(GameObject* pGameObject, float updateInterval = 1.f);

		~FPS() override;
		void Update() override;

		FPS(const FPS& other) = delete;
		FPS(FPS&& other) = delete;
		FPS& operator=(const FPS& other) = delete;
		FPS& operator=(FPS&& other) = delete;
	private:
		TextRenderer* m_pTextRenderer;
		float m_timeTillUpdate{ 0.f };
		float m_timeInterval;
	};
}
