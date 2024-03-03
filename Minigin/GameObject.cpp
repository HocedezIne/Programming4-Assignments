#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"
#include "TransformComponent.h"

engine::GameObject::GameObject(const glm::vec3 pos) :
	m_LocalPosition(pos), m_WorldPosition(m_LocalPosition)
{}

engine::GameObject::~GameObject() = default;

void engine::GameObject::Update(const float deltaTime)
{
	for (const auto& comp: m_Components)
	{
		if (auto ucomp = std::dynamic_pointer_cast<IUpdatable>(comp))
		{
			ucomp->Update(deltaTime);
		}
	}
}

void engine::GameObject::Render() const
{
	for (const auto& comp : m_Components)
	{
		if (auto rcomp = std::dynamic_pointer_cast<IRenderable>(comp))
		{
			rcomp->Render();
		}
	}
}

void engine::GameObject::ProcessDeletion()
{
	auto it = m_Components.begin();
	while (it != m_Components.end())
	{
		if ((*it)->IsMarkedForDeletion()) it = m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), (*it)), m_Components.end());
		else ++it;
	}
}

const glm::vec3 engine::GameObject::GetWorldPosition()
{
	if (m_PositionFlag) UpdateWorldPosition();

	return m_WorldPosition;
}

void engine::GameObject::UpdateWorldPosition()
{
	if (m_PositionFlag)
	{
		if (m_Parent == nullptr) m_WorldPosition = m_LocalPosition;
		else m_WorldPosition = m_Parent->GetWorldPosition() + m_LocalPosition;
	}

	m_PositionFlag = false;
}

bool engine::GameObject::IsChild(GameObject* obj)
{
	for (const auto& child : m_Children)
	{
		if (obj == child) return true;
	}

	return false;
}

void engine::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (IsChild(parent) || parent == this || m_Parent == parent) return;

	if (parent == nullptr) SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPosition) SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
		SetPositionDirty();
	}

	if (m_Parent) m_Parent->DetachChild(this);
	m_Parent = parent;
	if (m_Parent) m_Parent->AttachChild(this);
}