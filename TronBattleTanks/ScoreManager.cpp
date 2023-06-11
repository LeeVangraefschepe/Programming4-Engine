#include "ScoreManager.h"
#include "ResourceManager.h"
#include <string>
#include <fstream>
#include <ranges>
#include <sstream>
#include <vector>

dae::ScoreManager::ScoreManager()
{
	//Load from file
	if (std::ifstream input{ ResourceManager::GetInstance().GetPath() + "Score.dat", std::ios::binary }; input.is_open())
	{
		for (int i{}; i < static_cast<int>(m_maxScores); ++i)
		{
			std::vector<char> buffer(m_maxChars);
			input.read(buffer.data(), static_cast<int>(m_maxChars));
			std::string username{buffer.data(), m_maxChars};

			int score{};
			input.read(reinterpret_cast<char*>(&score), sizeof(int));

			m_scores.insert(std::pair(score, username));
		}
	}
	//else
	//{
	//	for (int i{}; i < static_cast<int>(m_maxScores); ++i)
	//	{
	//		m_scores.insert(std::pair(0, "   "));
	//	}
	//}
	const int amountOfLoadedScores = static_cast<int>(m_scores.size());
	for (int i{amountOfLoadedScores}; i < static_cast<int>(m_maxScores); ++i)
	{
		m_scores.insert(std::pair(0, "   "));
	}
}

dae::ScoreManager::~ScoreManager()
{
	//Save to file
	if (std::ofstream output{ ResourceManager::GetInstance().GetPath() + "Score.dat", std::ios::binary };  output.is_open())
	{
		for (const auto& score : m_scores)
		{
			output.write(score.second.c_str(), static_cast<int>(m_maxChars));
			output.write(reinterpret_cast<const char*>(&score.first), sizeof(int));
		}
		output.close();
	}
}

int dae::ScoreManager::GetScore() const
{
	return m_score;
}

void dae::ScoreManager::AddScore(int amount)
{
	m_score += amount;
}

void dae::ScoreManager::ResetScore()
{
	m_score = 0;
}

void dae::ScoreManager::SubmitScore(const std::string& username)
{
	for (const auto& key : m_scores | std::views::keys)
	{
		if (key < m_score)
		{
			m_scores.erase(key);
			m_scores.insert(std::pair{m_score, username});
			break;
		}
	}
	ResetScore();
}

std::vector<std::string> dae::ScoreManager::GetScores() const
{
	std::vector<std::string> textScores{};
	textScores.reserve(m_maxScores);
	for (const auto& value : m_scores)
	{
		std::stringstream ss{};
		ss << value.first << ": " << value.second;
		textScores.emplace_back(ss.str());
	}
	return textScores;
}
