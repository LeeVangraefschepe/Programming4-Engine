#pragma once
#include <map>
#include <string>
#include <vector>

#include "Singleton.h"

namespace dae
{
	class ScoreManager final : public Singleton<ScoreManager>
	{
	public:
		int GetScore() const;
		void AddScore(int amount);
		void ResetScore();
		void SubmitScore(const std::string& username);

		std::vector<std::string> GetScores() const;

	private:
		            friend class Singleton;
		ScoreManager();
		~ScoreManager() override;

		int m_score{};

		const size_t m_maxChars{ 3 };
		const size_t m_maxScores{10};
		std::multimap<int, std::string> m_scores{};
	};
}
