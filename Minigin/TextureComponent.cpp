#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"

void engine::TextureComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto pos = m_pOwner.lock()->GetComponent<TransformComponent>()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void engine::TextureComponent::SetTexture(const std::string& fileName)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(fileName);
}

void engine::TextureComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;
}

engine::TextureComponent::TextureComponent(std::shared_ptr<GameObject> pOwner, const std::string& fileName) : Component(pOwner)
{
	Component::DependencyCheck<TransformComponent>(this);

	if (!fileName.empty()) m_Texture = ResourceManager::GetInstance().LoadTexture(fileName);
	else m_Texture = nullptr;
}