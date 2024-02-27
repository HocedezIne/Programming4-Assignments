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

#include <iostream>

void load()
{
	auto& scene = engine::SceneManager::GetInstance().CreateScene("Demo");

	try
	{
	auto go = std::make_shared<engine::GameObject>();
	go->AddComponent<engine::TransformComponent>(std::make_shared<engine::TransformComponent>(go));
	go->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(go, "background.tga"));
	scene.Add(go);

	go = std::make_shared<engine::GameObject>();
	go->AddComponent<engine::TransformComponent>(std::make_shared<engine::TransformComponent>(go, 216.f, 180.f));
	go->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(go, "logo.tga"));
	scene.Add(go);

	auto font = engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<engine::GameObject>();
	go->AddComponent<engine::TransformComponent>(std::make_shared<engine::TransformComponent>(go, 80.f, 20.f));
	go->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(go));
	go->AddComponent<engine::TextComponent>(std::make_shared<engine::TextComponent>(go, "Programming 4 Assignment", font));
	scene.Add(go);

	go = std::make_shared<engine::GameObject>();
	go->AddComponent<engine::TransformComponent>(std::make_shared<engine::TransformComponent>(go));
	go->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(go));
	go->AddComponent<engine::TextComponent>(std::make_shared<engine::TextComponent>(go, "0 FPS", font));
	go->AddComponent<engine::FPSComponent>(std::make_shared<engine::FPSComponent>(go));
	scene.Add(go);


	// Testing other GameObject functions
	//if (go->HasComponent<engine::FPSComponent>())
	//{
	//	auto tc = go->GetComponent<engine::FPSComponent>();
	//	if (tc)
	//	{
	//		go->RemoveComponent<engine::FPSComponent>(tc);
	//	}
	//}

	}
	catch (const engine::MissingComponentDependency& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
}

int main(int, char*[]) {
	engine::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}