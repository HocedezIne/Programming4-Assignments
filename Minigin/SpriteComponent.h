#pragma once
#include "Component.h"

namespace engine
{
	class SpriteComponent final : public Component
	{
	public:
		SpriteComponent(/*std::shared_ptr<*/GameObject*/*>*/);
		~SpriteComponent() = default;
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;
	};
}