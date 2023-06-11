#include "LevelComponent.h"

#include <iostream>
#include <sstream>
#include <glm/detail/func_geometric.inl>

#include "GameObject.h"
#include "GridComponent.h"

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
	LoadPlayerSpawns();
	LoadEnemySpawns();
}

void dae::LevelComponent::SpawnPlayers(std::vector<std::function<void(const glm::vec2& position)>>& players) const
{
	const int playerCount = static_cast<int>(players.size());
	for (int i{}; i < playerCount; ++i)
	{
		players[i](m_playerSpawns[rand() % m_playerSpawns.size()]);
	}
}

void dae::LevelComponent::SpawnEnemies(std::function<void(const glm::vec2& position)> enemy, std::function<void(const glm::vec2& position)> recognizer) const
{
	for (const auto& position : m_enemySpawns)
	{
		if (rand()%2 == 0)
		{
			recognizer(position);
			continue;
		}
		enemy(position);
	}
}

void dae::LevelComponent::LoadPlayerSpawns()
{
	const auto& data = m_pGrid->GetRawGrid();

	const int heightSize = static_cast<int>(data.size());
	for (int height{}; height < heightSize; ++height)
	{
		const auto& dataWidth = data[height];
		const int widthSize = static_cast<int>(dataWidth.size());

		for (int width{}; width < widthSize; ++width)
		{
			if (const auto& id = dataWidth[width]; id == 5 || id == 6)
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

void dae::LevelComponent::LoadEnemySpawns()
{
	const auto& data = m_pGrid->GetRawGrid();

	const int heightSize = static_cast<int>(data.size());
	for (int height{}; height < heightSize; ++height)
	{
		const auto& dataWidth = data[height];
		const int widthSize = static_cast<int>(dataWidth.size());

		for (int width{}; width < widthSize; ++width)
		{
			if (const auto& id = dataWidth[width]; id == 4)
			{
				//Check if value isn't already defined nearby
				bool isDefined{};
				for (const auto& v : m_enemySpawns)
				{
					if (distance(v, { width,height }) < 3)
					{
						isDefined = true;
						break;
					}
				}
				if (!isDefined)
				{
					m_enemySpawns.emplace_back(width, height);
					std::cout << "Player spawn: " << width << ", " << height << "\n";
				}
			}
		}
	}

	for (auto& pos : m_enemySpawns)
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
