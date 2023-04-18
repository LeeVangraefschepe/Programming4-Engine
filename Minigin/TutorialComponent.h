#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TutorialComponent final : public BaseComponent
	{
	public:
		explicit TutorialComponent(GameObject* pGameObject);
		void Render() override;
	};
}