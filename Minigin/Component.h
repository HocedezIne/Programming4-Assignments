#pragma once
#include "GameObject.h"

namespace engine {
	class Component {
	public:
		virtual ~Component() = default;

		void MarkDeletion() { m_DeleteFlag = true; };
		bool IsMarkedForDeletion() const { return m_DeleteFlag; };

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

	protected:
		Component(std::weak_ptr<GameObject> pOwner) : m_pOwner(pOwner) {};

		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; };

	private:
		bool m_DeleteFlag{ false };
		const std::weak_ptr<GameObject> m_pOwner;
	};

	// ------------------------------------------------
	// Interfaces to extend base component with
	// ------------------------------------------------
	class IUpdatable {
	public:
		virtual void Update(const float deltaTime) = 0;
		virtual ~IUpdatable() = default;
	};

	class IRenderable {
	public:
		virtual void Render() const = 0;
		virtual ~IRenderable() = default;
	};
}