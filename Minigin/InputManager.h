#pragma once
#include <SDL.h>
#include "Singleton.h"
#include "Commands.h"
#include "Controller.h"
#include <map>

namespace engine
{
	enum class KeyState
	{
		Pressed,
		Released,
		Held
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		void AddKeyboardCommand(SDL_Scancode key, KeyState state, std::unique_ptr<Command> command);
		
	private:
		void ProcessControllerStates();
		void ProcessKeyboardState();

		using ControllerKeyState = std::pair< std::pair<unsigned, Controller::Buttons>, KeyState>;
		using ControllerCommands = std::map< ControllerKeyState, std::unique_ptr<Command> >;
		ControllerCommands m_ControllerCommands{};

		using KeyboardCommands = std::map< std::pair<SDL_Scancode, KeyState>, std::unique_ptr<Command> >;
		KeyboardCommands m_KeyboardCommands{};

		std::vector<Uint8> m_PrevKeyboardState;
	};

}
