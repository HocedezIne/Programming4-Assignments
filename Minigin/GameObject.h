#pragma once
#include <memory>
#include <vector>

namespace engine
{
	class Component;

	class GameObject final
	{
	public:
		void Update(const float deltaTime);
		void Render() const;

		void MarkDeletion() { m_DeleteFlag = true; };
		bool IsMarkedForDeletion() const { return m_DeleteFlag; };
		void ProcessDeletion();

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

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<std::shared_ptr<Component>> m_Components;

		bool m_DeleteFlag{ false };
	};
}
