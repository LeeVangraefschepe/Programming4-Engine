#pragma once
#include <functional>
#include <glm/vec2.hpp>

#include "BaseComponent.h"
namespace dae
{
	class GridComponent;
	class LevelComponent : public BaseComponent
	{
	public:
		LevelComponent(GameObject* pGameObject);

		void LoadLevel(int id);
		void SpawnPlayers(std::vector<std::function<void(const glm::vec2& position)>>& players) const;
		void SpawnEnemies(std::function<void(const glm::vec2& position)> enemy, std::function<void(const glm::vec2& position)> recognizer) const;
		glm::vec2 GetRandomSpawn() const;

		LevelComponent(const LevelComponent& other) = delete;
		LevelComponent(LevelComponent&& other) = delete;
		LevelComponent& operator=(const LevelComponent& other) = delete;
		LevelComponent& operator=(LevelComponent&& other) = delete;
	private:

		void LoadPlayerSpawns();
		void LoadEnemySpawns();
		void ReadOutRaw() const;

		GridComponent* m_pGrid;
		std::vector<glm::vec2> m_playerSpawns{};
		std::vector<glm::vec2> m_enemySpawns{};

		static inline constexpr glm::vec2 m_cellSize { 12, 12 };
	};
}