#include "EventQueue.h"

#include <iostream>

void dae::EventQueue::AddListener(const Event& e, Observer<void>* observer)
{
	auto& observers{ m_Observers[e] };
	observers.push_back(observer);
}
void dae::EventQueue::SendMessage(const Event& e)
{
	//Error handling
	if (m_NrEventsQueued >= m_EventBufferSize)
	{
		return;
	}

	const unsigned int curIdx{ (m_EventBufferStart + m_NrEventsQueued) % m_EventBufferSize };
	m_EventQueue[curIdx] = e;
	++m_NrEventsQueued;
}
void dae::EventQueue::NotifyListeners()
{
	Event e{""};
	while (PollEvent(e))
	{
		std::cout << "Event fired: " << e.GetName() << "\n";
		auto& observers{ m_Observers[e] };
		for (const auto& observer : observers)
		{
			observer->OnNotify(e, nullptr);
		}
	}
}
bool dae::EventQueue::PollEvent(Event& e)
{
	if (m_NrEventsQueued == 0) return false;

	e = m_EventQueue[m_EventBufferStart];

	++m_EventBufferStart %= m_EventBufferSize;
	--m_NrEventsQueued;

	return true;
}