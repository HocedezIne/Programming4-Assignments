#pragma once
#include "Component.h"
#include "TransformComponent.h"

namespace engine
{
	class RotatorComponent final: public Component, public IUpdatable
	{
	public:
		void Update(const float deltaTime) override;

		RotatorComponent(std::shared_ptr<GameObject> pOwner, const int radius, const float speed);
		~RotatorComponent() = default;
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;

	private:
		TransformComponent* m_TransformComp;

		const int m_Radius;
		const float m_Speed;
		const float m_MaxAngle{ float(M_PI * 2) };
		float m_Angle{};
	};
}