#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include "BaseComponent.h"
#include "Commands.h"

namespace dae
{
	class Transform;
	class GameModeManager : public BaseComponent
	{
	public:
		enum GameModes
		{
			singleplayer = 0,
			versus,
			coop
		};
		explicit GameModeManager(GameObject* pGameObject, std::vector<glm::vec2> cursorPositions);
		~GameModeManager() override;

		void Update() override;
		static GameModes GetGameMode() { return m_gamemode; }

		GameModeManager(const GameModeManager& other) = delete;
		GameModeManager(GameModeManager&& other) = delete;
		GameModeManager& operator=(const GameModeManager& other) = delete;
		GameModeManager& operator=(GameModeManager&& other) = delete;

	private:
		std::vector<glm::vec2> m_positions;
		std::vector<LambdaCommand*> m_commands{};
		int m_selectedGameMode{};

		Transform* m_pCursorTransfrom;

		static inline GameModes m_gamemode{};
	};
}