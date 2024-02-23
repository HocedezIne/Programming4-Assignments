#pragma once

namespace dae {
	class Component {
	public:
		Component() = default;
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
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