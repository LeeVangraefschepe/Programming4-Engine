#pragma once
namespace dae
{
	class Event;
	class GameObject;

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(const Event& event, GameObject* entity) = 0;
	};
}