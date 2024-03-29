#pragma once
#include <memory>
#include <string>
#include "Component.h"
#include "TransformComponent.h"
#include "Texture2D.h"

namespace engine
{
	class TextureComponent final : public Component, public IRenderable
	{
	public:
		void Render() const override;

		void SetTexture(const std::string& fileName);
		void SetTexture(std::shared_ptr<Texture2D> texture);

		TextureComponent(std::shared_ptr<GameObject> pOwner, const std::string& fileName = {});
		~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

	private:
		std::shared_ptr<Texture2D> m_Texture;
		TransformComponent* m_TransformComp;
	};
}

