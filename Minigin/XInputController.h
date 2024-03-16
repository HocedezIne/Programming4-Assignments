#pragma once
#include "Controller.h"
#include <windows.h>
#include <Xinput.h>

namespace engine
{
	class Controller::Impl
	{
	public:
		Impl() = default;
		~Impl() = default;

		void PollInput();

		bool IsDownThisFrame(unsigned int buttonMask) const { return buttonsPressedThisFrame & buttonMask; };
		bool IsUpThisFrame(unsigned int buttonMask) const { return buttonsReleasedThisFrame & buttonMask; };;
		//bool IsPressedThisFrame(unsigned int buttonMask) const;

	private:
		XINPUT_STATE m_State;
		XINPUT_STATE m_PrevState;

		uint8_t buttonsPressedThisFrame{};
		uint8_t buttonsReleasedThisFrame{};
	};
}