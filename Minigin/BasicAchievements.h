#pragma once
#include <string>

#include "Observer.h"
#include "Singleton.h"

namespace dae
{
	class GameEvent;

	class BasicAchievements : public Observer<GameObject>, public Singleton<BasicAchievements>
	{
	public:
		virtual void OnNotify(const Event& event, GameObject*) override;
		static void ClearAchievements();
	private:
		static void UnlockAchievement(const std::string& name);
	};
}