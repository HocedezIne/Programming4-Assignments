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
		void AddControllerCommand(Controller::Button button, KeyState state, std::unique_ptr<Command> command, unsigned int controllerId = 0);
		
		void AddController();

	private:
		void ProcessControllerStates();
		void ProcessKeyboardState();

		using ControllerButtonState = std::pair< std::pair<unsigned int, Controller::Button>, KeyState>;
		using ControllerCommands = std::map< ControllerButtonState, std::unique_ptr<Command> >;
		ControllerCommands m_ControllerCommands{};
		std::vector<std::unique_ptr<Controller>> m_Controllers;

		using KeyboardCommands = std::map< std::pair<SDL_Scancode, KeyState>, std::unique_ptr<Command> >;
		KeyboardCommands m_KeyboardCommands{};

		std::vector<Uint8> m_PrevKeyboardState;
	};

}
