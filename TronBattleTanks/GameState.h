#pragma once
class GameState final
{
public:
	GameState() = default;

	void OnLevelStarted();
	void OnLevelCompleted();
	bool GetLevelId(int& id) const;

	GameState(const GameState& other) = delete;
	GameState(GameState&& other) = delete;
	GameState& operator=(const GameState& other) = delete;
	GameState& operator=(GameState&& other) = delete;
private:
	int m_currentLevel{};
	const int m_lastLevel{ 2 };
};

