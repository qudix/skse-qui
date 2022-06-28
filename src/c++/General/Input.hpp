#pragma once

namespace General::Input
{
	enum : uint32_t
	{
		kInvalidButton = static_cast<uint32_t>(-1),
		kKeyboardOffset = 0u,
		kMouseOffset = 256u,
		kGamepadOffset = 266u,
		kPS3Offset = 302u
	};

	inline uint32_t GetKeyboardIndex(RE::BSWin32KeyboardDevice::Key a_key)
	{
		using Key = RE::BSWin32KeyboardDevice::Key;

		uint32_t index;
		switch (a_key) {
			case Key::kEscape:
				index = 1u;
				break;
			case Key::kEnter:
				index = 28u;
				break;
			default:
				index = kInvalidButton;
				break;
		}

		return index != kInvalidButton ? index + kKeyboardOffset : kInvalidButton;
	}

	// Button Panel Index
	inline uint32_t GetGamepadIndex(RE::BSWin32GamepadDevice::Key a_key)
	{
		using Key = RE::BSWin32GamepadDevice::Key;

		uint32_t index;
		switch (a_key) {
			case Key::kUp:
				index = 0u;
				break;
			case Key::kDown:
				index = 1u;
				break;
			case Key::kLeft:
				index = 2u;
				break;
			case Key::kRight:
				index = 3u;
				break;
			case Key::kStart:
				index = 4u;
				break;
			case Key::kBack:
				index = 5u;
				break;
			case Key::kLeftThumb:
				index = 6u;
				break;
			case Key::kRightThumb:
				index = 7u;
				break;
			case Key::kLeftShoulder:
				index = 8u;
				break;
			case Key::kRightShoulder:
				index = 9u;
				break;
			case Key::kA:
				index = 10u;
				break;
			case Key::kB:
				index = 11u;
				break;
			case Key::kX:
				index = 12u;
				break;
			case Key::kY:
				index = 13u;
				break;
			case Key::kLeftTrigger:
				index = 14u;
				break;
			case Key::kRightTrigger:
				index = 15u;
				break;
			default:
				index = kInvalidButton;
				break;
		}

		return index != kInvalidButton ? index + kGamepadOffset : kInvalidButton;
	}
}
