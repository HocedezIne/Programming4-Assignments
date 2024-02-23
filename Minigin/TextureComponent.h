#pragma once
#include <memory>
#include <string>
#include "Component.h"
#include "Transform.h"
#include "Texture2D.h"

namespace dae
{
	class TextureComponent final : public Component, public IRenderable
	{
	public:
		void Render() const override;

		void SetPosition(const float x, const float y);

		TextureComponent(const std::string& fileName);
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

	private:
		Transform m_Transform{};
		std::shared_ptr<Texture2D> m_Texture;
	};
}

