#include "XInputController.h"

void engine::Controller::Impl::PollInput()
{
	CopyMemory(&m_PrevState, &m_State, sizeof(XINPUT_STATE));
	ZeroMemory(&m_State, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_State);

	if (m_State.dwPacketNumber == m_PrevState.dwPacketNumber) return;

	uint8_t buttonChanges = static_cast<uint8_t>(m_State.Gamepad.wButtons ^ m_PrevState.Gamepad.wButtons);
	buttonsPressedThisFrame = buttonChanges & m_State.Gamepad.wButtons;
	buttonsReleasedThisFrame = buttonChanges & (~m_State.Gamepad.wButtons);
}