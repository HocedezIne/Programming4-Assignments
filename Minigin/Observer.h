#pragma once
#include <vector>
#include <any>

enum class Event
{
	PlayerDied,
	UIDataUpdated,
	IncreaseScore
};

class Observer
{
public: 
	virtual ~Observer() = default;

	virtual void OnNotify(void* caller, Event event, const std::any& args) = 0;
};

class Subject
{
public:
	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);

protected: 
	void NotifyObservers(void* caller, Event event, const std::any& args);

private:
	std::vector<Observer*> m_Observers;
};