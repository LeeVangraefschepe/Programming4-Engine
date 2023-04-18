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
				std::thread t{ [this]() { UnlockAchievement(win); } };
				t.detach();
			}
		}
		break;
	default: break;
	}
}
void dae::BasicAchievements::ClearAchievements()
{
	SteamUserStats()->ClearAchievement(m_achievementIds[win]);
}
void dae::BasicAchievements::UnlockAchievement(Achievements achievement)
{
	if (m_achievementUnlocked[achievement])
	{
		return;
	}
	m_achievementUnlocked[achievement] = true;
	SteamUserStats()->SetAchievement(m_achievementIds[achievement]);
	SteamUserStats()->StoreStats();
}