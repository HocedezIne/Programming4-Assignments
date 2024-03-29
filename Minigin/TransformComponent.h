#pragma once
#include <glm/glm.hpp>
#include "Component.h"

namespace engine
{
	class TransformComponent final : public Component
	{
	public:
		TransformComponent(std::shared_ptr<GameObject>, float x=0, float y=0, float z=0);
		~TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(const glm::vec3 pos);
		void SetPosition(const float x, const float y, const float z);
	private:
		glm::vec3 m_position;
	};
}
