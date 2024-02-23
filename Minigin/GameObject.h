#pragma once
#include <memory>
#include <unordered_map>
// #include "Transform.h"
#include "Component.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		virtual void Update(const float deltaTime);
		virtual void Render() const;

		template<typename T>
		void AddComponent(std::shared_ptr<T> comp)
		{
			static_assert(std::is_base_of<Component, T>::value, "Item must derrive from Component class");
			m_Components[typeid(T).name()] = comp;
		};
		
		template<typename T>
		void RemoveComponent() {};

		template<typename T>
		std::shared_ptr<T> GetComponent() 
		{
			auto it = m_Components.find(typeid(T).name());
			if (it != m_Components.end())
				return std::dynamic_pointer_cast<T>(it->second);

			return nullptr;
		};

		template<typename T>
		bool HasComponent() 
		{
			return m_Components.find(typeid(T).name()) != m_Components.end();
		};

		//void SetTexture(const std::string& filename);
		//void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::unordered_map<std::string, std::shared_ptr<Component>> m_Components;

		//Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		//std::shared_ptr<Texture2D> m_texture{};
	};
}
