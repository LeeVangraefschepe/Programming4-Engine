#include "BasicAchievements.h"
#include "Event.h"
#include <iostream>

void dae::BasicAchievements::OnNotify(const Event& event, GameObject*)
{
	if (event.IsValid() == false)
	{
		return;
	}
	std::cout << "Event triggerd: " << event.GetName() << "\n";
	if (event == Event{"DIED"})
	{
		std::cout << "Died achievement unlocked\n";
	}
}