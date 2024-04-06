#pragma once
#include "Component.h"
#include "TextComponent.h"
#include "Observer.h"

#include <functional>

namespace engine
{
	typedef int(*DataGetterFunction)(const std::string&);
	class StatusComponent;

	class UILinkingComponent : public Component, public Observer
	{
	public:
		UILinkingComponent(std::shared_ptr<GameObject> pOwner, std::string base, StatusComponent* sc);
		~UILinkingComponent() = default;
		UILinkingComponent(const UILinkingComponent& other) = delete;
		UILinkingComponent(UILinkingComponent&& other) = delete;
		UILinkingComponent& operator=(const UILinkingComponent& other) = delete;
		UILinkingComponent& operator=(UILinkingComponent&& other) = delete;

		virtual void OnNotify(void* caller, Event event, const std::any& args) override;

	private:
		std::string m_Base;
		TextComponent* m_TextComp;
		StatusComponent* m_StatusComp;
	};
}