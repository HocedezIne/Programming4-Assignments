#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

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
	//const auto& pos = m_Transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
//}
//
//void dae::GameObject::SetPosition(float x, float y)
//{
//	m_Transform.SetPosition(x, y, 0.0f);
//}
