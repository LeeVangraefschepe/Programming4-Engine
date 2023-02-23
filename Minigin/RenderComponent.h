#pragma once
#include "BaseComponent.h"

namespace dae
{
	class RenderComponent : public BaseComponent
	{
	public:
		RenderComponent(GameObject* pGameObject)
			: BaseComponent(pGameObject)
		{
			
		};
		virtual ~RenderComponent() override = default;

		virtual void Render() const = 0;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
	};
}
