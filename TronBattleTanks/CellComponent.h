#pragma once
#include "BaseComponent.h"

namespace dae
{
	class CellComponent final : public BaseComponent
	{
	public:
		CellComponent(GameObject* pGameObject);
		~CellComponent() override = default;

		CellComponent(const CellComponent& other) = delete;
		CellComponent(CellComponent&& other) = delete;
		CellComponent& operator=(const CellComponent& other) = delete;
		CellComponent& operator=(CellComponent&& other) = delete;
	};
}
