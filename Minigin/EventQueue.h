#pragma once
#include <unordered_map>
#include "Singleton.h"
#include "Event.h"
#include "Observer.h"

namespace dae
{
	class EventQueue final : public Singleton<EventQueue>
	{
	public:
		explicit EventQueue() = default;
		~EventQueue() override = default;

		void AddListener(const Event& e, Observer* listener);

		void SendMessage(const Event& e);
		void NotifyListeners();

		EventQueue(const EventQueue&) = delete;
		EventQueue(EventQueue&&) = delete;
		EventQueue& operator= (const EventQueue&) = delete;
		EventQueue& operator= (const EventQueue&&) = delete;
	private:
		bool PollEvent(Event& e);

		constexpr static unsigned int m_EventBufferSize{ 10 };
		Event m_EventQueue[m_EventBufferSize]{};
		unsigned int m_EventBufferStart{};
		unsigned int m_NrEventsQueued{};

		std::unordered_map<Event, std::vector<Observer*>> m_Observers;
	};
}
