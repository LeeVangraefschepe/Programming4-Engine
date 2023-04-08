#include "EventQueue.h"
#include <iostream>

void dae::EventQueue::AddListener(unsigned int eventId, Observer<void>* observer)
{
	auto& observers{ m_Observers[eventId] };
	observers.push_back(observer);
}
void dae::EventQueue::SendMessage(unsigned int eventId)
{
	//Error handling
	if (m_NrEventsQueued >= m_EventBufferSize)
	{
		return;
	}

	const unsigned int curIdx{ (m_EventBufferStart + m_NrEventsQueued) % m_EventBufferSize };
	m_EventQueue[curIdx] = eventId;
	++m_NrEventsQueued;
}
void dae::EventQueue::NotifyListeners()
{
	unsigned int eventId{};
	while (PollEvent(eventId))
	{
		std::cout << "Event fired: " << eventId << "\n";
		auto& observers{ m_Observers[eventId] };
		for (const auto& observer : observers)
		{
			observer->OnNotify(eventId, nullptr);
		}
	}
}
bool dae::EventQueue::PollEvent(unsigned int& eventId)
{
	if (m_NrEventsQueued == 0) return false;

	eventId = m_EventQueue[m_EventBufferStart];

	++m_EventBufferStart %= m_EventBufferSize;
	--m_NrEventsQueued;

	return true;
}