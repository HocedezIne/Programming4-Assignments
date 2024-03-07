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
#include "RotatorComponent.h"
#include "Scene.h"

#include <iostream>

void load()
{
	auto& scene = engine::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<engine::GameObject>();
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
	go->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(go));
	go->AddComponent<engine::TextComponent>(std::make_shared<engine::TextComponent>(go, "0 FPS", font));
	go->AddComponent<engine::FPSComponent>(std::make_shared<engine::FPSComponent>(go));
	scene.Add(go);

	go = std::make_shared<engine::GameObject>();
	go->AddComponent<engine::TransformComponent>(std::make_shared<engine::TransformComponent>(go, 100.f, 300.f));
	scene.Add(go);

	auto goc1 = std::make_shared<engine::GameObject>();
	goc1->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(goc1, "bomberman.tga"));
	goc1->AddComponent<engine::RotatorComponent>(std::make_shared<engine::RotatorComponent>(goc1, 25, 5.f));
	goc1->SetParent(go.get(), false);
	scene.Add(goc1);

	auto goc2 = std::make_shared<engine::GameObject>();
	goc2->AddComponent<engine::TransformComponent>(std::make_shared<engine::TransformComponent>(goc2));
	goc2->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(goc2, "bomberman.tga"));
	goc2->AddComponent<engine::RotatorComponent>(std::make_shared<engine::RotatorComponent>(goc2, 30, 7.f));
	goc2->SetParent(goc1.get(), false);
	scene.Add(goc2);

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

int main(int, char*[]) {
	engine::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}