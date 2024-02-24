#include "TransformComponent.h"

dae::TransformComponent::TransformComponent(std::shared_ptr<GameObject> pOwner, float x, float y, float z) : Component(pOwner)
{
	SetPosition(x, y, z);
}

void dae::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}