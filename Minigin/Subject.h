#pragma once
#include <vector>

namespace dae
{
	class Observer;
	class Event;
	class GameObject;
	class Subject
	{
	public:
		explicit Subject(int maxObservers = 10);
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void Notify(const Event& event, GameObject* pGameObject) const;
	private:
		std::vector<Observer*> m_pObservers;
	};
}