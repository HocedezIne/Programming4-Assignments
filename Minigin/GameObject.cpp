#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"
#include "TransformComponent.h"

engine::GameObject::GameObject()
{
	AddComponent(std::make_shared<TransformComponent>(this));
	m_Transform = GetComponent<TransformComponent>().get();
}

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

void engine::GameObject::SetLocalPosition(const glm::vec3 pos)
{
	m_Transform->SetPosition(pos);
}

glm::vec3 engine::GameObject::GetWorldPosition() const
{
	if (m_Parent != nullptr) return m_Parent->GetWorldPosition() + m_Transform->GetPosition();
	return m_Transform->GetPosition();
}

//void engine::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
//{
//	if (parent == this || m_Parent == parent) return;
//
//	if (parent == nullptr) SetLocalPosition(GetWorldPosition());
//	else
//	{
//		if (keepWorldPosition) SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
//		SetPositionDirty();
//	}
//
//	if (m_Parent) m_Parent->RemoveChild(this);
//	m_Parent = parent;
//	if (m_Parent) m_Parent->AddChild(this);
//}

void engine::GameObject::SetPositionDirty()
{
	m_PositionFlag = true;
	for (auto& child : m_Children)
	{
		child->SetPositionDirty();
	}
}