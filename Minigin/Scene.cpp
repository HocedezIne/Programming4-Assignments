#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace engine;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	object->MarkDeletion();
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update(const float deltaTime)
{
	for(auto& object : m_objects)
	{
		object->Update(deltaTime);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void Scene::ProcessDeletion()
{
	auto it = m_objects.begin();
	while (it != m_objects.end())
	{
		if ((*it)->IsMarkedForDeletion()) it = m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), (*it)), m_objects.end());
		else
		{
			(*it)->ProcessDeletion();
			++it;
		}
	}
}