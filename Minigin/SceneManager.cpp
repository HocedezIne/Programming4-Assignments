#include "SceneManager.h"
#include "Scene.h"

void engine::SceneManager::Update(const float deltaTime)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(deltaTime);
	}
}

void engine::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void engine::SceneManager::ProcessDeletion()
{
	for (const auto& scene : m_scenes)
	{
		scene->ProcessDeletion();
	}
}

engine::Scene& engine::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
