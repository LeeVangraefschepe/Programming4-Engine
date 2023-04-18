#pragma once
#include <string>
#include "Observer.h"
#include "Singleton.h"

namespace dae
{
	class PlayerComponent;
	class BasicAchievements : public Observer<PlayerComponent>, public Singleton<BasicAchievements>
	{
		enum Achievements
		{
			win
		};
	public:
		BasicAchievements();
		virtual void OnNotify(unsigned int eventId, PlayerComponent*) override;
		static void ClearAchievements();
	private:
		static void UnlockAchievement(Achievements achievement);

		static inline constexpr int m_size = 1;
		static inline bool m_achievementUnlocked[m_size]{};
		static inline const char* m_achievementIds[m_size] = { "ACH_WIN_ONE_GAME"};
	};
}