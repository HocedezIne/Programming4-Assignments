#include "FPSComponent.h"
#include <iomanip>
#include <sstream>

void dae::FPSComponent::Update(const float deltaTime)
{
	m_FrameCount++;
	m_TotalTime += deltaTime;
	if (m_TotalTime > 1.f)
	{
		TextComponent::SetText(std::to_string(m_FrameCount / m_TotalTime) + " FPS");
		TextComponent::Update(deltaTime);

		m_FrameCount = 0;
		m_TotalTime = 0.f;
	}
}