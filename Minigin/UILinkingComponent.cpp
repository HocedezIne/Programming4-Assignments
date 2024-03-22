#include "UILinkingComponent.h"
#include "StatusComponent.h"

engine::UILinkingComponent::UILinkingComponent(std::shared_ptr<GameObject> pOwner, std::string base) : Component(pOwner),
	m_Base(base)
{
	if (!pOwner->HasComponent<TextComponent>())
	{
		pOwner->AddComponent<TextComponent>(std::make_shared<TextComponent>(pOwner, m_Base + ": "));
	}
	m_TextComp = pOwner->GetComponent<TextComponent>().get();
}

void engine::UILinkingComponent::OnNotify(void* caller, Event event, const std::any& args)
{
	args;

	if (event == Event::UIDataUpdated)
	{
		auto definedCaller = static_cast<StatusComponent*>(caller);
		m_TextComp->SetText(m_Base + ": " + std::to_string(definedCaller->GetData(m_Base)));
	}
}
