#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

namespace dae
{
	class CellComponent final : public BaseComponent
	{
	public:
		CellComponent(GameObject* pGameObject);
		~CellComponent() override = default;
	};
}
