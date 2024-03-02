#include "TransformComponent.h"

engine::TransformComponent::TransformComponent(GameObject* pOwner, float x, float y, float z) : Component(pOwner)
{
	SetPosition(x, y, z);
}

void engine::TransformComponent::SetPosition(const glm::vec3 pos)
{
	m_position = pos;
}
void engine::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	SetPosition(glm::vec3{ x,y,z });
}
