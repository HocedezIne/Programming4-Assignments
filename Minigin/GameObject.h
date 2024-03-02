#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>

namespace engine
{
	class Component;
	class TransformComponent;

	class GameObject final
	{
	public:
		void Update(const float deltaTime);
		void Render() const;

		void MarkDeletion() { m_DeleteFlag = true; };
		bool IsMarkedForDeletion() const { return m_DeleteFlag; };
		void ProcessDeletion();

		//void SetParent(GameObject* parent, bool keepWorldPosition);

		void SetLocalPosition(const glm::vec3 pos);
		glm::vec3 GetWorldPosition() const;

		template<typename T>
		void AddComponent(std::shared_ptr<T> comp)
		{
			static_assert(std::is_base_of<Component, T>::value, "Item must derrive from Component class");
			m_Components.push_back(std::move(comp));
		};
		
		template<typename T>
		void RemoveComponent(std::shared_ptr<T> comp) 
		{
			comp->MarkDeletion();
		};

		template<typename T>
		std::shared_ptr<T> GetComponent() 
		{
			auto it = std::find_if(m_Components.begin(), m_Components.end(),
				[typeName = typeid(T).name()](const auto& ptr) {
					return ptr && typeid(*ptr) == typeid(T);
				});

			if (it != m_Components.end())
				return std::dynamic_pointer_cast<T>(*it);

			return nullptr;
		};

		template<typename T>
		bool HasComponent() 
		{
			auto it = std::find_if(m_Components.begin(), m_Components.end(),
				[typeName = typeid(T).name()](const auto& ptr) {
					return ptr && typeid(*ptr) == typeid(T);
				});
			return it != m_Components.end();
		};

		GameObject();

		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		//void AddChild(GameObject* child) { m_Children.push_back(child); };
		//void RemoveChild(GameObject* child) { m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), (child)), m_Children.end()); };

		void SetPositionDirty();

		std::vector<std::shared_ptr<Component>> m_Components;
		GameObject* m_Parent{ nullptr };
		std::vector<GameObject*> m_Children{};
		TransformComponent* m_Transform;

		bool m_DeleteFlag{ false };
		bool m_PositionFlag{ false };
	};
}
