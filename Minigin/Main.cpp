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
#include "InputManager.h"
#include "GameObject.h"
#include "Component.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "TextureComponent.h"
#include "RotatorComponent.h"
#include "CachePlotComponent.h"
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
	go->AddComponent<engine::TransformComponent>(std::make_shared<engine::TransformComponent>(go, 100.f, 200.f));
	go->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(go, "bomberman.png"));
	engine::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_W, engine::KeyState::Held, std::make_unique<engine::MoveCommand>(go.get(), glm::vec3{0.f,-1.f,0.f}, 50.f));
	engine::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_A, engine::KeyState::Held, std::make_unique<engine::MoveCommand>(go.get(), glm::vec3{-1.f,0.f,0.f}, 50.f));
	engine::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_S, engine::KeyState::Held, std::make_unique<engine::MoveCommand>(go.get(), glm::vec3{0.f,1.f,0.f}, 50.f));
	engine::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_D, engine::KeyState::Held, std::make_unique<engine::MoveCommand>(go.get(), glm::vec3{1.f,0.f,0.f}, 50.f));
	scene.Add(go);

	engine::InputManager::GetInstance().AddController();

	go = std::make_shared<engine::GameObject>();
	go->AddComponent<engine::TransformComponent>(std::make_shared<engine::TransformComponent>(go, 125.f, 200.f));
	go->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(go, "balloom.png"));
	engine::InputManager::GetInstance().AddControllerCommand(engine::Controller::Button::DPadUp, engine::KeyState::Held, std::make_unique<engine::MoveCommand>(go.get(), glm::vec3{ 0.f, -1.f,0.f }, 100.f), 0);
	engine::InputManager::GetInstance().AddControllerCommand(engine::Controller::Button::DPadLeft, engine::KeyState::Held, std::make_unique<engine::MoveCommand>(go.get(), glm::vec3{ -1.f, 0.f,0.f }, 100.f), 0);
	engine::InputManager::GetInstance().AddControllerCommand(engine::Controller::Button::DPadDown, engine::KeyState::Held, std::make_unique<engine::MoveCommand>(go.get(), glm::vec3{ 0.f, 1.f,0.f }, 100.f), 0);
	engine::InputManager::GetInstance().AddControllerCommand(engine::Controller::Button::DPadRight, engine::KeyState::Held, std::make_unique<engine::MoveCommand>(go.get(), glm::vec3{ 1.f, 0.f,0.f }, 100.f), 0);
	scene.Add(go);
}

int main(int, char*[]) {
	engine::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}