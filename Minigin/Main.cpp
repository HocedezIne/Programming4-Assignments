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
#include "TextComponent.h"
#include "FPSComponent.h"
#include "TextureComponent.h"
#include "Scene.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	auto bg = std::make_shared<dae::TextureComponent>("background.tga");
	go->AddComponent<dae::TextureComponent>(bg);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	auto logo = std::make_shared<dae::TextureComponent>("logo.tga");
	logo->SetPosition(216, 180);
	go->AddComponent<dae::TextureComponent>(logo);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<dae::TextComponent>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextComponent>(to);
	scene.Add(go);

	auto fps = std::make_shared<dae::FPSComponent>(font);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::FPSComponent>(fps);
	scene.Add(go);

	auto test = new dae::GameObject();
	test->HasComponent<dae::FPSComponent>();

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