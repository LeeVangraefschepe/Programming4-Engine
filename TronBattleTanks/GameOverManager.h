#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Command;

	class GameOverManager final : public BaseComponent
	{
	public:
		explicit GameOverManager(GameObject* pGameObject);
		~GameOverManager() override;

		GameOverManager(const GameOverManager& other) = delete;
		GameOverManager(GameOverManager&& other) = delete;
		GameOverManager& operator=(const GameOverManager& other) = delete;
		GameOverManager& operator=(GameOverManager&& other) = delete;
	private:
		Command* m_pKeyboardCommand;
		Command* m_pControllerCommand;
	};
}
