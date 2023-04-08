#pragma once
namespace dae
{
	class Event;
	class GameObject;

	template <typename T>
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(const Event& event, T* entity) = 0;
	};
}