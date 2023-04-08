#pragma once
#include <functional>
#include <unordered_map>
#include "Singleton.h"
#include "Event.h"

namespace dae
{
	class EventQueue final : public Singleton<EventQueue>
	{
		using Listener = std::function<void()>;

	public:
		explicit EventQueue() = default;
		~EventQueue() override = default;

		void AddListener(const Event& e, const Listener& listener);

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

		std::unordered_map<Event, std::vector<Listener>> m_Observers;
	};
}
