#pragma once
namespace dae
{
	class GameObject;

	template <typename T>
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(unsigned int eventId, T* entity) = 0;
	};
}