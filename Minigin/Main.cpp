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

	auto go = std::make_shared<engine::GameObject>();
	go->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(go.get(), "background.tga"));
	scene.Add(go);

	go = std::make_shared<engine::GameObject>();
	go->SetLocalPosition(glm::vec3{ 216.f, 180.f, 0.f });
	go->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(go.get(), "logo.tga"));
	scene.Add(go);

	auto font = engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<engine::GameObject>();
	go->SetLocalPosition(glm::vec3{ 80.f, 20.f, 0.f });
	go->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(go.get()));
	go->AddComponent<engine::TextComponent>(std::make_shared<engine::TextComponent>(go.get(), "Programming 4 Assignment", font));
	scene.Add(go);

	go = std::make_shared<engine::GameObject>();
	go->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(go.get()));
	go->AddComponent<engine::TextComponent>(std::make_shared<engine::TextComponent>(go.get(), "0 FPS", font));
	go->AddComponent<engine::FPSComponent>(std::make_shared<engine::FPSComponent>(go.get()));
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

int main(int, char*[]) {
	engine::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}