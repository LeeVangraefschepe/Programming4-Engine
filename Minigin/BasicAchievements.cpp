#include "BasicAchievements.h"
#include <iostream>
#include <isteamuserstats.h>
#include <thread>
#include "PlayerComponent.h"
#include "ScoreComponent.h"

dae::BasicAchievements::BasicAchievements()
{

}

void dae::BasicAchievements::OnNotify(unsigned int eventId, PlayerComponent* enity)
{
	switch (auto event = static_cast<PlayerComponent::Events>(eventId))
	{
	case PlayerComponent::score:
		{
			if (enity->GetData()->scoreComponent->GetScore() >= 500)
			{
				std::thread t{ [this]() { UnlockAchievement("ACH_WIN_ONE_GAME"); } };
				t.detach();
			}
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