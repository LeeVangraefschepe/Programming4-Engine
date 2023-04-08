#pragma once
#include <functional>
#include <unordered_map>
#include "Singleton.h"
#include "Observer.h"

namespace dae
{
	class EventQueue final : public Singleton<EventQueue>
	{
	public:
		explicit EventQueue() = default;
		~EventQueue() override = default;

		void AddListener(unsigned int eventId, Observer<void>* observer);

		void SendMessage(unsigned int eventId);
		void NotifyListeners();

		EventQueue(const EventQueue&) = delete;
		EventQueue(EventQueue&&) = delete;
		EventQueue& operator= (const EventQueue&) = delete;
		EventQueue& operator= (const EventQueue&&) = delete;
	private:
		bool PollEvent(unsigned int& eventId);

		constexpr static unsigned int m_EventBufferSize{ 10 };
		unsigned int m_EventQueue[m_EventBufferSize]{};
		unsigned int m_EventBufferStart{};
		unsigned int m_NrEventsQueued{};

		std::unordered_map<unsigned int, std::vector<Observer<void>*>> m_Observers{};
	};
}
