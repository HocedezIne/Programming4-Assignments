#include <stdexcept>
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "TextureComponent.h"

dae::TextComponent::TextComponent(std::shared_ptr<GameObject> pOwner, const std::string& text, std::shared_ptr<Font> font)
	: Component(pOwner), m_needsUpdate(true), m_text(text), m_font(std::move(font))
{
	Component::DependencyCheck<TextureComponent>(this);
}

void dae::TextComponent::Update(const float deltaTime)
{
	deltaTime;

	if (m_needsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pOwner.lock()->GetComponent<TextureComponent>()->SetTexture(std::make_shared<Texture2D>(texture));
		m_needsUpdate = false;
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}