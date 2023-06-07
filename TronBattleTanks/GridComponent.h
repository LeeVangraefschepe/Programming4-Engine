#pragma once
#include <string>
#include <glm/vec2.hpp>
#include "BaseComponent.h"

namespace dae
{
	class CellComponent;
	class GridComponent final : public dae::BaseComponent
	{
	public:
		GridComponent(GameObject* pGameObject, const glm::vec2& cellSize);
		void LoadGrid(const std::string& path);
		~GridComponent() override = default;

		GridComponent(const GridComponent& other) = delete;
		GridComponent(GridComponent&& other) = delete;
		GridComponent& operator=(const GridComponent& other) = delete;
		GridComponent& operator=(GridComponent&& other) = delete;
	private:
		void GenerateGrid(const std::vector<std::vector<int>>& data);
		std::vector<std::vector<CellComponent*>> m_Cells{};
		glm::vec2 m_CellSize;
	};
}