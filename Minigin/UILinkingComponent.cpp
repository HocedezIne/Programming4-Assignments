#include "UILinkingComponent.h"
#include "StatusComponent.h"

engine::UILinkingComponent::UILinkingComponent(std::shared_ptr<GameObject> pOwner, std::string base, StatusComponent* sc)  : Component(pOwner),
	m_Base(base), m_StatusComp(sc)
{
	if (!pOwner->HasComponent<TextComponent>())
	{
		pOwner->AddComponent<TextComponent>(std::make_shared<TextComponent>(pOwner, ""));
	}

	m_TextComp = pOwner->GetComponent<TextComponent>().get();
	m_TextComp->SetText(m_Base + ": " + std::to_string(m_StatusComp->GetData(m_Base)));
}

void engine::UILinkingComponent::OnNotify(void* caller, Event event, const std::any& args)
{
	args; caller;

	switch (event)
	{
	case Event::PlayerDied:
	case Event::EnemyDied:
		m_TextComp->SetText(m_Base + ": " + std::to_string(m_StatusComp->GetData(m_Base)));
		break;
	default:
		break;
	}
}
