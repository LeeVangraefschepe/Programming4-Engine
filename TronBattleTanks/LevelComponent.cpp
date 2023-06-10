#include "LevelComponent.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/detail/func_geometric.inl>

#include "GameObject.h"
#include "GridComponent.h"
#include "ResourceManager.h"

dae::LevelComponent::LevelComponent(GameObject* pGameObject) : BaseComponent(pGameObject)
{
	m_pGrid = pGameObject->AddComponent<GridComponent>(glm::vec2{ 12, 12 });
}

void dae::LevelComponent::LoadLevel(int id)
{
	std::stringstream ss{};
	ss << "Level/LevelLayout" << id << ".csv";
	m_pGrid->LoadGrid(ss.str());
	ReadOutRaw();
	LoadSpawns();
}

void dae::LevelComponent::SpawnPlayers(std::vector<std::function<void(const glm::vec2& position)>>& players) const
{
	const int playerCount = static_cast<int>(players.size());
	const int randomSpawnId = rand() % m_playerSpawns.size() - (playerCount - 1);
	for (int i{}; i < playerCount; ++i)
	{
		players[i](m_playerSpawns[randomSpawnId+i]);
	}
}

void dae::LevelComponent::LoadSpawns()
{
	const auto& data = m_pGrid->GetRawGrid();

	const int heightSize = static_cast<int>(data.size());
	for (int height{}; height < heightSize; ++height)
	{
		const auto& dataWidth = data[height];
		const int widthSize = static_cast<int>(dataWidth.size());

		for (int width{}; width < widthSize; ++width)
		{
			const auto& id = dataWidth[width];
			if (id == 5 || id == 6)
			{
				//Check if value isn't already defined nearby
				bool isDefined{};
				for (const auto& v : m_playerSpawns)
				{
					if (distance(v, { width,height }) < 3)
					{
						isDefined = true;
						break;
					}
				}
				if (!isDefined)
				{
					m_playerSpawns.emplace_back(width,height);
					std::cout << "Player spawn: " << width << ", " << height << "\n";
				}
			}
		}
	}

	for (auto& pos : m_playerSpawns)
	{
		pos *= m_cellSize;
	}
}

void dae::LevelComponent::ReadOutRaw() const
{
	const auto& data = m_pGrid->GetRawGrid();

	std::vector<int> amount{};
	amount.resize(10);

	const int heightSize = static_cast<int>(data.size());
	for (int height{}; height < heightSize; ++height)
	{
		const auto& dataWidth = data[height];
		const int widthSize = static_cast<int>(dataWidth.size());

		for (int width{}; width < widthSize; ++width)
		{
			const auto& id = dataWidth[width];
			++amount[id];
		}
	}

	for (int i{}; i < amount.size(); ++i)
	{
		std::cout << i << ": " << amount[i] << "\n";
	}
}
