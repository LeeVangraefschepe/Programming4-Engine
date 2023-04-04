#include "Subject.h"
#include "Observer.h"

dae::Subject::Subject(int maxObservers)
{
	m_pObservers = std::vector<Observer*>{};
	m_pObservers.resize(maxObservers);
}
void dae::Subject::AddObserver(Observer* observer)
{
	m_pObservers.emplace_back(observer);
}
void dae::Subject::RemoveObserver(Observer* observer)
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
void dae::Subject::Notify(const Event& event, GameObject* pGameObject) const
{
	for (const auto observer : m_pObservers)
	{
		if (observer)
		{
			observer->OnNotify(event, pGameObject);
		}
	}
}