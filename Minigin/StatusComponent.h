#pragma once
#include "Component.h"
#include "Observer.h"
#include <map>
#include <string>
#include <any>

namespace engine 
{
	class StatusComponent : public Component, public Observer
	{
	public:
		StatusComponent(std::shared_ptr<GameObject> pOwner);
		~StatusComponent() = default;
		StatusComponent(const StatusComponent& other) = delete;
		StatusComponent(StatusComponent&& other) = delete;
		StatusComponent& operator=(const StatusComponent& other) = delete;
		StatusComponent& operator=(StatusComponent&& other) = delete;

		void AddDataMapping(const std::string& keyword, int value);
		int GetData(const std::string& keyword) const;
		void UpdateData(const std::string& keyword, int value);
		void RemoveDataMapping(const std::string& keyword);

		virtual void OnNotify(void* caller, Event event);

	private:
		std::map<std::string, int> m_DataMap;
	};
}