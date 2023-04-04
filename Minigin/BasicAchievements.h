#pragma once
#include "Observer.h"
#include "Singleton.h"

namespace dae
{
	class BasicAchievements : public Observer, public Singleton<BasicAchievements>
	{
	public:
		virtual void OnNotify(const Event& event, GameObject* entity) override;
	};
}