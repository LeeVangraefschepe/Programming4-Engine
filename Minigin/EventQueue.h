#pragma once
#include <mutex>
#include <queue>

namespace dae
{
	template <typename Event>
class EventQueue
{
public:
    void Enqueue(const Event& event)
	{
        std::lock_guard lock(m_Mutex);
        m_Queue.push(event);
    }

    Event Dequeue()
	{
        std::lock_guard lock(m_Mutex);
        Event event = m_Queue.front();
        m_Queue.pop();
        return event;
    }

    bool IsEmpty()
	{
        std::lock_guard lock(m_Mutex);
        return m_Queue.empty();
    }

private:
    std::queue<Event> m_Queue;
    std::mutex m_Mutex;
};
}
