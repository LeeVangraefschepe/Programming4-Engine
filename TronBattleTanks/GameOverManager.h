#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Command;
	class TextRenderer;

	class GameOverManager final : public BaseComponent
	{
	public:
		explicit GameOverManager(GameObject* pGameObject);
		~GameOverManager() override;

		void Next();
		void Update() override;

		GameOverManager(const GameOverManager& other) = delete;
		GameOverManager(GameOverManager&& other) = delete;
		GameOverManager& operator=(const GameOverManager& other) = delete;
		GameOverManager& operator=(GameOverManager&& other) = delete;
	private:
		bool m_continueMenu{};
		void LoadScores() const;
		std::vector<Command*> m_pCommands{};
		int m_step{};
		static const int m_tagSize{ 3 };
		char m_tag[m_tagSize];
		TextRenderer* m_text[m_tagSize]{};
	};
}
