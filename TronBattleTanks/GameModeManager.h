#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include "BaseComponent.h"
#include "Commands.h"

namespace dae
{
	class GameModeManager : public BaseComponent
	{
	public:
		explicit GameModeManager(GameObject* pGameObject, std::vector<glm::vec2> cursorPositions);
		~GameModeManager() override;

		GameModeManager(const GameModeManager& other) = delete;
		GameModeManager(GameModeManager&& other) = delete;
		GameModeManager& operator=(const GameModeManager& other) = delete;
		GameModeManager& operator=(GameModeManager&& other) = delete;

	private:
		std::vector<glm::vec2> m_positions;
		std::vector<LambdaCommand*> m_commands{};
	};
}