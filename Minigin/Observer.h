#pragma once
#include <vector>

enum class Event
{
	PlayerDied
};

class Observer
{
public: 
	virtual ~Observer() = default;
	virtual void OnNotify(void* caller, Event event) = 0;
};

class Subject
{
public:
	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);

protected: 
	void NotifyObservers(void* caller, Event event);

private:
	std::vector<Observer*> m_Observers;
};