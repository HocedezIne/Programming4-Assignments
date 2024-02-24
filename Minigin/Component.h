#pragma once
#include "GameObject.h"
#include <stdexcept>

namespace dae {
	// ------------------------------------------------
	// Exception class
	// ------------------------------------------------
	class MissingComponentDependency : public std::runtime_error {
	public:
		MissingComponentDependency(const std::string& msg) : std::runtime_error(msg) {};
	};

	class Component {
	public:
		Component(std::shared_ptr<GameObject> pOwner) { m_pOwner = pOwner; };
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

	protected:
		template<typename Target, typename Caller>
		void DependencyCheck(Caller)
		{
			if (!m_pOwner->HasComponent<Target>())
			{
				std::string msg{ typeid(Caller).name() };
				msg += " cannot be added on GameObjects without a ";
				msg += typeid(Target).name();
				throw MissingComponentDependency( msg );
			}
		}


		std::shared_ptr<GameObject> m_pOwner;
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