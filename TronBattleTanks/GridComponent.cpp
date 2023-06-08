#include "GridComponent.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "CollisionComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "CellComponent.h"

dae::GridComponent::GridComponent(GameObject* pGameObject, const glm::vec2& cellSize):
BaseComponent(pGameObject),
m_CellSize{cellSize}
{
	
}
void dae::GridComponent::LoadGrid(const std::string& path)
{

	if (std::ifstream input{ ResourceManager::GetInstance().GetPath() + path }; input.is_open())
	{
		std::string line;
		std::vector<std::vector<int>> grid;
		while (std::getline(input, line))
		{
			std::vector<int> row;
			std::istringstream iss(line);
			std::string token;
			while (std::getline(iss, token, ',')) {
				row.push_back(std::stoi(token));
			}
			grid.push_back(row);
		}
		GenerateGrid(grid);
	}
	else
	{
		std::cout << "File not found " << ResourceManager::GetInstance().GetPath() << path << "\n";
	}
}

void dae::GridComponent::GenerateGrid(const std::vector<std::vector<int>>& data)
{
	const auto baseObject = BaseComponent::GetGameObject();
	const auto cellImage = ResourceManager::GetInstance().LoadTexture("Wall.png");
	const std::vector layers{0,1};

	const int heightSize = static_cast<int>(data.size());
	m_Cells.resize(heightSize);
	for (int height{}; height < heightSize; ++height)
	{
		const auto& dataWidth = data[height];
		const int widthSize = static_cast<int>(dataWidth.size());

		m_Cells[height].resize(widthSize);

		for (int width{}; width < widthSize; ++width)
		{
			const auto& id = dataWidth[width];
			if (id == 5)
			{
				
			}
			else if (id == 0)
			{
				const auto cellObj = new GameObject{};
				cellObj->SetParent(baseObject, false);

				cellObj->AddComponent<SpriteRenderer>(cellImage);

				const auto cellTransform = cellObj->GetComponent<Transform>();
				cellTransform->SetLocalPosition(static_cast<float>(width) * m_CellSize.x, static_cast<float>(height) * m_CellSize.y);

				cellObj->AddComponent<CollisionComponent>(layers)->SetSize(m_CellSize.x, m_CellSize.y);

				const auto cell = cellObj->AddComponent<CellComponent>();
				m_Cells[height][width] = cell;
			}
		}
	}
}
