#include "Observer.h"

void Subject::AddObserver(Observer* observer)
{
	auto it = std::find(m_Observers.begin(), m_Observers.end(), observer);
	if (it == m_Observers.end()) m_Observers.push_back(observer);
}

void Subject::RemoveObserver(Observer* observer)
{
	auto it = std::find(m_Observers.begin(), m_Observers.end(), observer);
	if (it != m_Observers.end()) m_Observers.erase(it);
}

void Subject::NotifyObservers(void* caller, Event event)
{
	for (auto& observer : m_Observers)
	{
		observer->OnNotify(caller, event);
	}
}
