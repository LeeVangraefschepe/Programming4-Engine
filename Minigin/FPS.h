#pragma once
#include "UpdateComponent.h"

namespace dae
{
	class FPS final : UpdateComponent
	{
	public:
		explicit FPS(GameObject* pGameObject);

		~FPS() override;
		void Update() override;

		
	};
}
