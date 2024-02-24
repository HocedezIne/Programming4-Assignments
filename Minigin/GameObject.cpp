#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(const float deltaTime)
{
	for (const auto& comp: m_Components)
	{
		if (auto ucomp = std::dynamic_pointer_cast<IUpdatable>(comp))
		{
			ucomp->Update(deltaTime);
		}
	}
}

void dae::GameObject::Render() const
{
	for (const auto& comp : m_Components)
	{
		if (auto rcomp = std::dynamic_pointer_cast<IRenderable>(comp))
		{
			rcomp->Render();
		}
	}
}