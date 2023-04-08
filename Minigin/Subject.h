#pragma once
#include <vector>
#include "Observer.h"

namespace dae
{
	class Event;
	class GameObject;

	template <typename T>
	class Subject
	{
	public:
		explicit Subject(int maxObservers = 10)
		{
			m_pObservers = std::vector<Observer<T>*>{};
			m_pObservers.reserve(maxObservers);
		}
		void AddObserver(Observer<T>* observer)
		{
			m_pObservers.emplace_back(observer);
		}
		void RemoveObserver(Observer<T>* observer)
		{
			for (auto it = m_pObservers.begin(); it != m_pObservers.end(); ++it)
			{
				if (*it == observer)
				{
					m_pObservers.erase(it);
					return;
				}
			}
		}
		void Notify(const Event& event, T* entity) const
		{
			for (const auto observer : m_pObservers)
			{
				if (observer)
				{
					observer->OnNotify(event, entity);
				}
			}
		}
	private:
		std::vector<Observer<T>*> m_pObservers;
	};
}