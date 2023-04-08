#include "BasicAchievements.h"
#include <iostream>
#include <isteamuserstats.h>
#include <thread>
#include "BasicEvents.h"

void dae::BasicAchievements::OnNotify(unsigned int eventId, GameObject*)
{
	std::cout << "Event triggerd: " << eventId << "\n";
	switch (auto event = static_cast<BasicEvents>(eventId))
	{
	case BasicEvents::PlayerDied:
		{
		std::cout << "Died achievement unlocked\n";
		std::thread t{ [this]() { UnlockAchievement("ACH_WIN_ONE_GAME"); } };
		t.detach();
		}
		break;
	default: break;
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