#pragma once
#include <string>
#include "Observer.h"
#include "Singleton.h"

namespace dae
{
	class PlayerComponent;
	class BasicAchievements : public Observer<PlayerComponent>, public Singleton<BasicAchievements>
	{
	public:
		BasicAchievements();
		virtual void OnNotify(unsigned int eventId, PlayerComponent*) override;
		static void ClearAchievements();
	private:
		static void UnlockAchievement(const std::string& name);
	};
}