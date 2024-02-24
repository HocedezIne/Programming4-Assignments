#include "FPSComponent.h"
#include <iomanip>
#include <sstream>

void dae::FPSComponent::Update(const float deltaTime)
{
	m_FrameCount++;
	m_TotalTime += deltaTime;
	if (m_TotalTime > 1.f)
	{
		std::ostringstream fpsString;
		fpsString << std::fixed << std::setprecision(1) << (m_FrameCount / m_TotalTime) << " FPS";
		m_pOwner.lock()->GetComponent<TextComponent>()->SetText(fpsString.str());

		m_FrameCount = 0;
		m_TotalTime = 0.f;
	}
}

dae::FPSComponent::FPSComponent(std::shared_ptr<GameObject> pOwner) : Component(pOwner)
{
	Component::DependencyCheck<TextComponent>(this);
}
