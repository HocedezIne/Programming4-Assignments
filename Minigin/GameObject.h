#pragma once
#include <memory>
#include <vector>
#include "glm/glm.hpp"

namespace engine
{
	class Component;
	class IUpdatable;
	class IRenderable;
	class TransformComponent;

	class GameObject final
	{
	public:
		void Update(const float deltaTime);
		void Render() const;

		void MarkDeletion() { m_DeleteFlag = true; };
		bool IsMarkedForDeletion() const { return m_DeleteFlag; };
		void ProcessDeletion();

		void SetLocalPosition(const glm::vec3 pos) { m_LocalPosition = pos; SetPositionDirty(); };
		const glm::vec3 GetLocalPosition() const { return m_LocalPosition; };
		const glm::vec3 GetWorldPosition();
		void UpdateWorldPosition();

		void SetParent(GameObject* parent, bool keepWorldPosition);

		template<typename T>
		void AddComponent(std::shared_ptr<T> comp)
		{
			static_assert(std::is_base_of<Component, T>::value, "Item must derrive from Component class");

			//if (IUpdatable* ucomp = std::dynamic_pointer_cast<IUpdatable>(comp.get())) m_UpdatableComponents.push_back(ucomp);
			//if (IRenderable* rcomp = std::dynamic_pointer_cast<IRenderable>(comp.get())) m_RenderableComponents.push_back(std::dynamic_pointer_cast<IRenderable>(rcomp);

			if (auto ucomp = std::dynamic_pointer_cast<IUpdatable>(comp)) m_UpdatableComponents.push_back(ucomp.get());
			if (auto rcomp = std::dynamic_pointer_cast<IRenderable>(comp)) m_RenderableComponents.push_back(rcomp.get());

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

		GameObject(const glm::vec3 = {});
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		void SetPositionDirty();

		void AttachChild(GameObject* child) { m_Children.push_back(child); };
		void DetachChild(GameObject* child) { m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), (child)), m_Children.end()); };
		bool IsChild(GameObject* obj);

		std::vector<std::shared_ptr<Component>> m_Components;
		std::vector<IUpdatable*> m_UpdatableComponents;
		std::vector<IRenderable*> m_RenderableComponents;
		std::vector<GameObject*> m_Children;

		GameObject* m_Parent{ nullptr };
		glm::vec3 m_LocalPosition;
		glm::vec3 m_WorldPosition;
		bool m_PositionFlag{ true };

		bool m_DeleteFlag{ false };
	};
}
