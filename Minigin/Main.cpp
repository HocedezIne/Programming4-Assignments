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
#include "TextComponent.h"
#include "Scene.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	//go->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	//go->SetTexture("logo.tga");
	//go->SetPosition(216, 180);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<dae::TextComponent>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextComponent>(to);
	scene.Add(go);

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