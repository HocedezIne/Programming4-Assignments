#pragma once
#include "Component.h"
#include "TextComponent.h"

namespace engine
{
	class FPSComponent final : public Component, public IUpdatable
	{
	public:
		void Update(const float deltaTime) override;

		FPSComponent(std::shared_ptr<GameObject> pOwner);
		~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

	private:
		int m_FrameCount{};
		float m_TotalTime{};

		TextComponent* m_TextComp;
	};
}
