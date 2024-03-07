#define _USE_MATH_DEFINES

#include "RotatorComponent.h"
#include <cmath>

void engine::RotatorComponent::Update(const float deltaTime)
{
	m_Angle += m_Speed * deltaTime;
	if (m_Angle > m_MaxAngle) m_Angle -= m_MaxAngle;

	const float x{ m_Radius * std::cos(m_Angle) };
	const float y{ m_Radius * std::sin(m_Angle) };

	m_TransformComp->SetPosition(x, y, 0.f);
}

engine::RotatorComponent::RotatorComponent(std::shared_ptr<GameObject> pOwner, const int radius, const float speed) : Component(pOwner),
	m_Radius(radius), m_Speed(speed)
{
	if (!pOwner->HasComponent<TransformComponent>())
	{
		pOwner->AddComponent<TransformComponent>(std::make_shared<TransformComponent>(pOwner));
	}
	m_TransformComp = pOwner->GetComponent<TransformComponent>().get();
}
