#include "FPSComponent.h"
#include <iomanip>
#include <sstream>

void engine::FPSComponent::Update(const float deltaTime)
{
	++m_FrameCount;
	m_TotalTime += deltaTime;
	if (m_TotalTime > 1.f)
	{
		std::ostringstream fpsString;
		fpsString << std::fixed << std::setprecision(1) << (m_FrameCount / m_TotalTime) << " FPS";
		m_TextComp->SetText(fpsString.str());

		m_FrameCount = 0;
		m_TotalTime = 0.f;
	}
}

engine::FPSComponent::FPSComponent(std::shared_ptr<GameObject> pOwner) : Component(pOwner)
{
	if (!pOwner->HasComponent<TextComponent>())
	{
		pOwner->AddComponent<TextComponent>(std::make_shared<TextComponent>(pOwner, "0 FPS"));
	}
	m_TextComp = pOwner->GetComponent<TextComponent>().get();
}
