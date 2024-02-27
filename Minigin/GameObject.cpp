#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

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