#include "Controller.h"

class engine::Controller::Impl
{
public:
	Impl(const unsigned int index) : m_Index(index) {};
	~Impl() = default;

	Impl(const Impl& other) = delete;
	Impl& operator=(const Impl& other) = delete;
	Impl(Impl&& other) = delete;
	Impl& operator=(Impl&& other) = delete;

	void PollInput()
	{
		CopyMemory(&m_PrevState, &m_State, sizeof(XINPUT_STATE));
		ZeroMemory(&m_State, sizeof(XINPUT_STATE));
		XInputGetState(m_Index, & m_State);

		uint8_t buttonChanges = static_cast<uint8_t>(m_State.Gamepad.wButtons ^ m_PrevState.Gamepad.wButtons);
		buttonsPressedThisFrame = buttonChanges & m_State.Gamepad.wButtons;
		buttonsReleasedThisFrame = buttonChanges & (~m_State.Gamepad.wButtons);
	};

	bool PressedThisFrame(Controller::Button button) const { return buttonsPressedThisFrame & static_cast<int>(button); };
	bool ReleasedThisFrame(Controller::Button button) const { return buttonsReleasedThisFrame & static_cast<int>(button); };
	bool HeldThisFrame(Controller::Button button) const { return m_State.Gamepad.wButtons & static_cast<int>(button); };

private:
	const unsigned int m_Index;

	XINPUT_STATE m_State{};
	XINPUT_STATE m_PrevState{};

	uint8_t buttonsPressedThisFrame{};
	uint8_t buttonsReleasedThisFrame{};
};

engine::Controller::Controller(const unsigned int index)
{
	m_Impl = new Impl{index};
};

engine::Controller::~Controller()
{
	delete m_Impl;
	m_Impl = nullptr;
};

void engine::Controller::PollInput()
{
	m_Impl->PollInput();
};

bool engine::Controller::PressedThisFrame(Controller::Button button) const
{ 
	return m_Impl->PressedThisFrame(button); 
};

bool engine::Controller::ReleasedThisFrame(Controller::Button button) const
{
	return m_Impl->ReleasedThisFrame(button); 
};

bool engine::Controller::HeldThisFrame(Controller::Button button) const
{ 
	return m_Impl->HeldThisFrame(button); 
};