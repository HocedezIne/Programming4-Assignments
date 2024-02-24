#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"

void dae::TextureComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto pos = m_pOwner->GetComponent<TransformComponent>()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

dae::TextureComponent::TextureComponent(std::shared_ptr<GameObject> pOwner, const std::string& fileName) : Component(pOwner)
{
	Component::DependencyCheck<TransformComponent>(this);

	m_Texture = ResourceManager::GetInstance().LoadTexture(fileName);
}