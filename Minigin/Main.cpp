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

	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<dae::TextComponent>(go, "Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	go = std::make_shared<dae::GameObject>();
	//go->AddComponent<dae::TextComponent>(to);
	scene.Add(go);

	//auto fps = std::make_shared<dae::FPSComponent>(go);
	go = std::make_shared<dae::GameObject>();
	//go->AddComponent<dae::FPSComponent>(fps);
	scene.Add(go);
	//}
	//catch (const dae::MissingComponentDependency& ex)
	//{
	//	assert(ex.what());
	//}

	// Testing other GameObject functions
	//if (go->HasComponent<dae::TextComponent>())
	//{
	//	auto tc = go->GetComponent<dae::TextComponent>();
	//	if (tc)
	//	{
	//		tc->SetText("I was found");
	//		go->RemoveComponent<dae::TextComponent>();
	//	}
	//}

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}