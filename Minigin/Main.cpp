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
#include "StatusComponent.h"
#include "UILinkingComponent.h"
#include "Scene.h"

#include <iostream>

#pragma warning (push)
#pragma warning (disable: 4996)
#include <steam_api.h>
#include "SteamAchievements.h"
#pragma warning (pop)

// Defining our achievements
enum EAchievements
{
	ACH_WIN_ONE_GAME = 0,
	ACH_WIN_100_GAMES = 1,
	ACH_TRAVEL_FAR_ACCUM = 2,
	ACH_TRAVEL_FAR_SINGLE = 3,
};

// Achievement array which will hold data about the achievements and their state
engine::Achievement_t g_Achievements[] =
{
	_ACH_ID(ACH_WIN_ONE_GAME, "Winner"),
	_ACH_ID(ACH_WIN_100_GAMES, "Champion"),
	_ACH_ID(ACH_TRAVEL_FAR_ACCUM, "Interstellar"),
	_ACH_ID(ACH_TRAVEL_FAR_SINGLE, "Orbiter"),
};

// Global access to Achievements object
engine::CSteamAchievements* g_SteamAchievements = NULL;

void load()
{
	auto& scene = engine::SceneManager::GetInstance().CreateScene("Demo");

#pragma region backgroundObjects

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
#pragma endregion backgroundObjects

#pragma region controlInfo
	font = engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	go = std::make_shared<engine::GameObject>();
	go->AddComponent<engine::TransformComponent>(std::make_shared<engine::TransformComponent>(go, 5.f, 75.f));
	go->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(go));
	go->AddComponent<engine::TextComponent>(std::make_shared<engine::TextComponent>(go, "WASD to move bomberman, C to kill him, X to increase score", font));
	scene.Add(go);

	go = std::make_shared<engine::GameObject>();
	go->AddComponent<engine::TransformComponent>(std::make_shared<engine::TransformComponent>(go, 5.f, 100.f));
	go->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(go));
	go->AddComponent<engine::TextComponent>(std::make_shared<engine::TextComponent>(go, "DPad to move balloom, X to kill him, B to increase score", font));
	scene.Add(go);
#pragma endregion controlInfo

#pragma region playerBomberman
	auto goUI = std::make_shared<engine::GameObject>();
	goUI->AddComponent<engine::TransformComponent>(std::make_shared<engine::TransformComponent>(goUI, 5.f, 135.f));
	goUI->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(goUI));
	goUI->AddComponent<engine::TextComponent>(std::make_shared<engine::TextComponent>(goUI, "Lives: 3", font));
	goUI->AddComponent<engine::UILinkingComponent>(std::make_shared<engine::UILinkingComponent>(goUI, "Lives"));
	scene.Add(goUI);

	go = std::make_shared<engine::GameObject>();
	go->AddComponent<engine::TransformComponent>(std::make_shared<engine::TransformComponent>(go, 100.f, 200.f));
	go->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(go, "bomberman.png"));
	engine::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_W, engine::KeyState::Held, std::make_unique<engine::MoveCommand>(go.get(), glm::vec3{0.f,-1.f,0.f}, 50.f));
	engine::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_A, engine::KeyState::Held, std::make_unique<engine::MoveCommand>(go.get(), glm::vec3{-1.f,0.f,0.f}, 50.f));
	engine::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_S, engine::KeyState::Held, std::make_unique<engine::MoveCommand>(go.get(), glm::vec3{0.f,1.f,0.f}, 50.f));
	engine::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_D, engine::KeyState::Held, std::make_unique<engine::MoveCommand>(go.get(), glm::vec3{1.f,0.f,0.f}, 50.f));

	auto sc = std::make_shared<engine::StatusComponent>(go);
	sc->AddObserver(goUI->GetComponent<engine::UILinkingComponent>().get());
	sc->AddDataMapping("Lives", 3);
	sc->AddDataMapping("Score", 0);

	auto killcmd = std::make_unique<engine::KillCommand>();
	killcmd->AddObserver(sc.get());
	engine::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_C, engine::KeyState::Pressed, std::move(killcmd));

	goUI = std::make_shared<engine::GameObject>();
	goUI->AddComponent<engine::TransformComponent>(std::make_shared<engine::TransformComponent>(goUI, 5.f, 160.f));
	goUI->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(goUI));
	goUI->AddComponent<engine::TextComponent>(std::make_shared<engine::TextComponent>(goUI, "Score: 0", font));
	goUI->AddComponent<engine::UILinkingComponent>(std::make_shared<engine::UILinkingComponent>(goUI, "Score"));
	scene.Add(goUI);

	sc->AddObserver(goUI->GetComponent<engine::UILinkingComponent>().get());
	sc->AddObserver(g_SteamAchievements);

	auto scorecmd = std::make_unique<engine::ScoreCommand>(100);
	scorecmd->AddObserver(sc.get());
	engine::InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_X, engine::KeyState::Pressed, std::move(scorecmd));

	go->AddComponent(sc);
	scene.Add(go);
#pragma endregion playerBomberman

#pragma region playerBalloom
	engine::InputManager::GetInstance().AddController();

	goUI = std::make_shared<engine::GameObject>();
	goUI->AddComponent<engine::TransformComponent>(std::make_shared<engine::TransformComponent>(goUI, 5.f, 185.f));
	goUI->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(goUI));
	goUI->AddComponent<engine::TextComponent>(std::make_shared<engine::TextComponent>(goUI, "Lives: 3", font));
	goUI->AddComponent<engine::UILinkingComponent>(std::make_shared<engine::UILinkingComponent>(goUI, "Lives"));
	scene.Add(goUI);

	go = std::make_shared<engine::GameObject>();
	go->AddComponent<engine::TransformComponent>(std::make_shared<engine::TransformComponent>(go, 125.f, 200.f));
	go->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(go, "balloom.png"));
	engine::InputManager::GetInstance().AddControllerCommand(engine::Controller::Button::DPadUp, engine::KeyState::Held, std::make_unique<engine::MoveCommand>(go.get(), glm::vec3{ 0.f, -1.f,0.f }, 100.f), 0);
	engine::InputManager::GetInstance().AddControllerCommand(engine::Controller::Button::DPadLeft, engine::KeyState::Held, std::make_unique<engine::MoveCommand>(go.get(), glm::vec3{ -1.f, 0.f,0.f }, 100.f), 0);
	engine::InputManager::GetInstance().AddControllerCommand(engine::Controller::Button::DPadDown, engine::KeyState::Held, std::make_unique<engine::MoveCommand>(go.get(), glm::vec3{ 0.f, 1.f,0.f }, 100.f), 0);
	engine::InputManager::GetInstance().AddControllerCommand(engine::Controller::Button::DPadRight, engine::KeyState::Held, std::make_unique<engine::MoveCommand>(go.get(), glm::vec3{ 1.f, 0.f,0.f }, 100.f), 0);
	
	sc = std::make_shared<engine::StatusComponent>(go);
	sc->AddObserver(goUI->GetComponent<engine::UILinkingComponent>().get());
	sc->AddDataMapping("Lives", 3);
	sc->AddDataMapping("Score", 0);

	killcmd = std::make_unique<engine::KillCommand>();
	killcmd->AddObserver(sc.get());
	engine::InputManager::GetInstance().AddControllerCommand(engine::Controller::Button::X, engine::KeyState::Pressed, std::move(killcmd));

	goUI = std::make_shared<engine::GameObject>();
	goUI->AddComponent<engine::TransformComponent>(std::make_shared<engine::TransformComponent>(goUI, 5.f, 210.f));
	goUI->AddComponent<engine::TextureComponent>(std::make_shared<engine::TextureComponent>(goUI));
	goUI->AddComponent<engine::TextComponent>(std::make_shared<engine::TextComponent>(goUI, "Score: 0", font));
	goUI->AddComponent<engine::UILinkingComponent>(std::make_shared<engine::UILinkingComponent>(goUI, "Score"));
	scene.Add(goUI);

	sc->AddObserver(goUI->GetComponent<engine::UILinkingComponent>().get());
	sc->AddObserver(g_SteamAchievements);

	scorecmd = std::make_unique<engine::ScoreCommand>(100);
	scorecmd->AddObserver(sc.get());
	engine::InputManager::GetInstance().AddControllerCommand(engine::Controller::Button::B, engine::KeyState::Pressed, std::move(scorecmd));

	go->AddComponent(sc);
	scene.Add(go);
#pragma endregion playerBaloom
}

int main(int, char*[]) {
	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Seam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Successfully initialized steam." << std::endl;
		g_SteamAchievements = new engine::CSteamAchievements(g_Achievements, 4);
	}

	engine::Minigin engine("../Data/");
	engine.Run(load);

	SteamAPI_Shutdown();
	if (g_SteamAchievements) delete g_SteamAchievements;

    return 0;
}