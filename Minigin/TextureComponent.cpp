#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

void dae::TextureComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto& pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void dae::TextureComponent::SetPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

dae::TextureComponent::TextureComponent(const std::string& fileName)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(fileName);
}