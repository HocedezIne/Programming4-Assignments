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
		Component(GameObject* pOwner) : m_pOwner(pOwner) {};

		const GameObject* GetOwner() const { return m_pOwner; };

	private:
		const GameObject* m_pOwner;
		bool m_DeleteFlag{ false };
	};

	// ------------------------------------------------
	// Interfaces to extend base component with
	// ------------------------------------------------
	class IUpdatable {
	public:
		virtual void Update(const float deltaTime) = 0;
	};

	class IRenderable {
	public:
		virtual void Render() const = 0;
	};
}