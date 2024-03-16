#include "Controller.h"
#include "XInputController.h"

engine::Controller::Controller() :
	m_Impl(new Impl())
{};

void engine::Controller::PollInput() 
{ 
	m_Impl->PollInput(); 
};

bool engine::Controller::IsDownThisFrame(unsigned int buttonMask) const 
{ 
	return m_Impl->IsDownThisFrame(buttonMask); 
};

bool engine::Controller::IsUpThisFrame(unsigned int buttonMask) const 
{ 
	return m_Impl->IsUpThisFrame(buttonMask);
};

//bool engine::Controller::IsPressedThisFrame(unsigned int buttonMask) const 
//{ 
//	return m_Impl->IsPressedThisFrame(buttonMask); 
//};