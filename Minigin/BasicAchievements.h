#pragma once
#include <string>

#include "Observer.h"
#include "Singleton.h"

namespace dae
{
	class BasicAchievements : public Observer, public Singleton<BasicAchievements>
	{
	public:
		virtual void OnNotify(const Event& event, GameObject* entity) override;
		static void ClearAchievements();
	private:
		static void UnlockAchievement(const std::string& name);
	};
}