#include "BasicAchievements.h"
#include "Event.h"
#include <iostream>
#include <isteamuserstats.h>
#include <thread>

void dae::BasicAchievements::OnNotify(const Event& event, GameObject*)
{
	if (event.IsValid() == false)
	{
		return;
	}
	std::cout << "Event triggerd: " << event.GetName() << "\n";
	if (event == Event{"PlayerDied"})
	{
		std::cout << "Died achievement unlocked\n";
		std::thread t{ [this]() { UnlockAchievement("ACH_WIN_ONE_GAME"); } };
		t.detach();
	}
}
void dae::BasicAchievements::ClearAchievements()
{
	SteamUserStats()->ClearAchievement("ACH_WIN_ONE_GAME");
}
void dae::BasicAchievements::UnlockAchievement(const std::string& name)
{
	SteamUserStats()->SetAchievement(name.c_str());
	SteamUserStats()->StoreStats();
}