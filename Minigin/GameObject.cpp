#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(const float deltaTime)
{
	for (const auto& pair : m_Components)
	{
		if (auto comp = std::dynamic_pointer_cast<IUpdatable>(pair.second))
		{
			comp->Update(deltaTime);
		}
	}
}

void dae::GameObject::Render() const
{
	for (const auto& pair : m_Components)
	{
		if (auto comp = std::dynamic_pointer_cast<IRenderable>(pair.second))
		{
			comp->Render();
		}
	}
}