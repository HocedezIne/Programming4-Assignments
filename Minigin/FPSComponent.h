#pragma once
#include "TextComponent.h"

namespace dae
{
	class FPSComponent final : public TextComponent
	{
	public:
		void Update(const float deltaTime) override;

		FPSComponent(std::shared_ptr<Font> font);
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

	private:
		int m_FrameCount{};
		float m_TotalTime{};
	};
}
