#pragma once
#include "BaseComponent.h"

namespace dae
{
	class UpdateComponent : BaseComponent
	{
	public:
		UpdateComponent(GameObject* pGameObject)
			: BaseComponent(pGameObject)
		{

		};
		virtual ~UpdateComponent() override = default;

		virtual void Update() = 0;

		UpdateComponent(const UpdateComponent& other) = delete;
		UpdateComponent(UpdateComponent&& other) = delete;
		UpdateComponent& operator=(const UpdateComponent& other) = delete;
		UpdateComponent& operator=(UpdateComponent&& other) = delete;
	};
}