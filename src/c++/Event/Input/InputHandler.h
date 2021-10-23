#pragma once

#include "Event/EventHandler.h"

namespace Event
{
	class KeyHandler :
		public InputHandler
	{
	public:
		KeyHandler() = default;

		void Handle(RE::InputEvent* const& a_event) override;

	private:
		using EventType = RE::INPUT_EVENT_TYPE;
		using DeviceType = RE::INPUT_DEVICE;

		static constexpr std::uint32_t INVALID = 282;  // ???

		enum : uint32_t
		{
			kInvalid = static_cast<uint32_t>(-1),
			kKeyboardOffset = 0,
			kMouseOffset = 256
		};

		RE::BSWin32KeyboardDevice::Key AsKeyboardKey(int64_t a_key);

		void ProcessKeyboard(const RE::ButtonEvent& a_event);
		//void ProcessGamepad(const RE::ButtonEvent& a_event);
	};
}
