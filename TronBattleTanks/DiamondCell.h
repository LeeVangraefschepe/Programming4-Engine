#pragma once
#include "BaseComponent.h"

namespace dae
{
	class DiamondCell final : public BaseComponent
	{
	public:
		DiamondCell(GameObject* pGameObject);
		~DiamondCell() override = default;

		DiamondCell(const DiamondCell& other) = delete;
		DiamondCell(DiamondCell&& other) = delete;
		DiamondCell& operator=(const DiamondCell& other) = delete;
		DiamondCell& operator=(DiamondCell&& other) = delete;
	};
}
