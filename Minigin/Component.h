#pragma once
#include "GameObject.h"
#include <stdexcept>

namespace engine {
	// ------------------------------------------------
	// Exception class
	// ------------------------------------------------
	class MissingComponentDependency : public std::runtime_error {
	public:
		MissingComponentDependency(const std::string& msg) : std::runtime_error(msg) {};
	};

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
		Component(std::weak_ptr<GameObject> pOwner) { m_pOwner = pOwner; };

		template<typename Target, typename Caller>
		void DependencyCheck(Caller)
		{
			if (!m_pOwner.lock()->HasComponent<Target>())
			{
				std::string msg{ typeid(Caller).name() };
				msg += " cannot be added on GameObjects without a ";
				msg += typeid(Target).name();
				throw MissingComponentDependency( msg );
			}
		}


		std::weak_ptr<GameObject> m_pOwner;

	private:
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