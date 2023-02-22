#pragma once
#include "BaseComponent.h"

namespace dae
{
	class RenderComponent : BaseComponent
	{
	public:
		RenderComponent() = default;
		virtual ~RenderComponent() override = default;

		virtual void Render() = 0;
		virtual void Update() override = 0;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
	private:
	};
}
