#include <stdexcept>
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Font.h"
#include "TextureComponent.h"

engine::TextComponent::TextComponent(std::shared_ptr<GameObject>  pOwner, const std::string& text, std::shared_ptr<Font> font)
	: Component(pOwner), m_needsUpdate(true), m_text(text)
{
	if (!pOwner->HasComponent<TextureComponent>())
	{
		pOwner->AddComponent<TextureComponent>(std::make_shared<TextureComponent>(pOwner));
	}
	m_TextureComp = pOwner->GetComponent<TextureComponent>().get();

	if (font != nullptr) m_font = std::move(font);
	else m_font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
}

void engine::TextComponent::Update(const float deltaTime)
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
		m_TextureComp->SetTexture(std::make_shared<Texture2D>(texture));
		m_needsUpdate = false;
	}
}

// This implementation uses the "dirty flag" pattern
void engine::TextComponent::SetText(const std::string& text)
{
	if(m_text != text) m_text = text;
	m_needsUpdate = true;
}