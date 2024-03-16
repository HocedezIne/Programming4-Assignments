#pragma once
#include <memory>

namespace engine
{
	class Controller
	{
	public:
		Controller();
		~Controller() = default;

		void PollInput();

		bool IsDownThisFrame(unsigned int buttonMask) const;
		bool IsUpThisFrame(unsigned int buttonMask) const;
		//bool IsPressedThisFrame(unsigned int buttonMask) const;

		enum class Buttons {

		};

	private:
		class Impl;
		std::unique_ptr<Impl> m_Impl;
	};
}