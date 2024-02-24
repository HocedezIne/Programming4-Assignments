#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Component.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "TextureComponent.h"
#include "Scene.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//try
	//{
	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TransformComponent>(std::make_shared<dae::TransformComponent>(go));
	go->AddComponent<dae::TextureComponent>(std::make_shared<dae::TextureComponent>(go, "background.tga"));
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TransformComponent>(std::make_shared<dae::TransformComponent>(go, 216.f, 180.f));
	go->AddComponent<dae::TextureComponent>(std::make_shared<dae::TextureComponent>(go, "logo.tga"));
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TransformComponent>(std::make_shared<dae::TransformComponent>(go, 80.f, 20.f));
	go->AddComponent<dae::TextureComponent>(std::make_shared<dae::TextureComponent>(go));
	go->AddComponent<dae::TextComponent>(std::make_shared<dae::TextComponent>(go, "Programming 4 Assignment", font));
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TransformComponent>(std::make_shared<dae::TransformComponent>(go));
	go->AddComponent<dae::TextureComponent>(std::make_shared<dae::TextureComponent>(go));
	go->AddComponent<dae::TextComponent>(std::make_shared<dae::TextComponent>(go, "0 FPS", font));
	go->AddComponent<dae::FPSComponent>(std::make_shared<dae::FPSComponent>(go));
	scene.Add(go);
	//}
	//catch (const dae::MissingComponentDependency& ex)
	//{
	//	assert(ex.what());
	//}

	// Testing other GameObject functions
	if (go->HasComponent<dae::FPSComponent>())
	{
		auto tc = go->GetComponent<dae::FPSComponent>();
		if (tc)
		{
			go->RemoveComponent<dae::FPSComponent>(tc);
		}
	}

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}