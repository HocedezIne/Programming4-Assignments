#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>
#include <memory>
#include <algorithm>
#include <functional>

bool engine::InputManager::ProcessInput(const float deltaTime)
{

	if (m_PrevKeyboardState.size() == 0)
	{
		m_PrevKeyboardState.reserve(SDL_NUM_SCANCODES);
		m_PrevKeyboardState.assign(SDL_NUM_SCANCODES, 0);
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}

		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	ProcessKeyboardState(deltaTime);
	ProcessControllerStates(deltaTime);

	return true;
}

void engine::InputManager::AddKeyboardCommand(SDL_Scancode key, KeyState state, std::unique_ptr<Command> command)
{
	m_KeyboardCommands.insert(std::make_pair(std::make_pair(key, state), std::move(command)));
}

void engine::InputManager::ProcessKeyboardState(const float deltaTime)
{
	// updating keyboard state
	auto keyboardState = SDL_GetKeyboardState(NULL);

	std::vector<Uint8> currentState{ keyboardState, keyboardState + SDL_NUM_SCANCODES };

	std::vector<Uint8> changedKeys(SDL_NUM_SCANCODES);
	std::vector<Uint8> pressedKeys(SDL_NUM_SCANCODES);
	std::vector<Uint8> releasedKeys(SDL_NUM_SCANCODES);

	std::transform(currentState.begin(), currentState.end(), m_PrevKeyboardState.begin(), changedKeys.begin(), std::bit_xor<Uint8>());
	std::transform(currentState.begin(), currentState.end(), changedKeys.begin(), pressedKeys.begin(), std::bit_and<Uint8>());
	std::transform(currentState.begin(), currentState.end(), changedKeys.begin(), releasedKeys.begin(),
		[](Uint8 curr, Uint8 changed) { return static_cast<Uint8>(curr & ~changed); });

	std::copy(currentState.begin(), currentState.end(), m_PrevKeyboardState.begin());

	// commands loop
	for (const auto& pair : m_KeyboardCommands)
	{
		switch (pair.first.second)
		{
		case KeyState::Pressed:
			if (pressedKeys[pair.first.first] == 1) pair.second->Execute(deltaTime);
			break;
		case KeyState::Released:
			if (releasedKeys[pair.first.first] == 1) pair.second->Execute(deltaTime);
			break;
		case KeyState::Held:
			if (currentState[pair.first.first] == 1 && m_PrevKeyboardState[pair.first.first] == 1) pair.second->Execute(deltaTime);
			break;
		}
	}
}

void engine::InputManager::AddControllerCommand(Controller::Button button, KeyState state, std::unique_ptr<Command> command, unsigned int controllerId)
{
	ControllerButtonState cbs = std::make_pair( std::make_pair(controllerId, button), state);
	m_ControllerCommands.insert(std::make_pair(cbs, std::move(command)));
}

void engine::InputManager::ProcessControllerStates(const float deltaTime)
{
	for (int idx{}; idx < int(m_Controllers.size()); ++idx)
	{
		m_Controllers[idx]->PollInput();
	}

	for (const auto& pair : m_ControllerCommands)
	{
		// check if for controller button is in right state

		switch (pair.first.second)
		{
		case KeyState::Pressed:
			if (m_Controllers[pair.first.first.first]->PressedThisFrame(pair.first.first.second))
			{
				pair.second->Execute(deltaTime);
			}
			break;
		case KeyState::Released:
			if (m_Controllers[pair.first.first.first]->ReleasedThisFrame(pair.first.first.second))
			{
				pair.second->Execute(deltaTime);
			}
			break;
		case KeyState::Held:
			if (m_Controllers[pair.first.first.first]->HeldThisFrame(pair.first.first.second))
			{
				pair.second->Execute(deltaTime);
			}
			break;
		}
	}
}

void engine::InputManager::AddController()
{
	m_Controllers.push_back(std::make_unique<Controller>(int(m_Controllers.size())));
}