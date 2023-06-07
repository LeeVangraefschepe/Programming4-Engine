#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TutorialComponent final : public BaseComponent
	{
	public:
		explicit TutorialComponent(GameObject* pGameObject);
		void Render() override;

		TutorialComponent(const TutorialComponent& other) = delete;
		TutorialComponent(TutorialComponent&& other) = delete;
		TutorialComponent& operator=(const TutorialComponent& other) = delete;
		TutorialComponent& operator=(TutorialComponent&& other) = delete;
	};
}