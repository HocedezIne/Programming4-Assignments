#pragma once
#include <memory>
#include <windows.h>
#include <Xinput.h>

namespace engine
{
	class Controller
	{
	public:
		enum class Button {
			DPadUp = 0x0001,
			DPadDown = 0x0002,
			DPadLeft = 0x0004,
			DPadRight = 0x0008
		};

		Controller(const unsigned int index);
		~Controller();

		Controller(const Controller& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(Controller&& other) = delete;

		void PollInput();

		bool PressedThisFrame(Controller::Button button) const;
		bool ReleasedThisFrame(Controller::Button button) const;
		bool HeldThisFrame(Controller::Button button) const;

	private:
		class Impl;
		Impl* m_Impl;
	};
}