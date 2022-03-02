#pragma once

namespace General::Input
{
	enum : uint32_t
	{
		kInvalidButton = static_cast<uint32_t>(-1),

		kESC = 1,
		kEnter = 28,

		kKeyboardOffset = 0,
		kMouseOffset = 256,
		kGamepadOffset = 266,
		kPS3Offset = 302
	};

	// Button Panel Index
	inline uint32_t GetGamepadIndex(RE::BSWin32GamepadDevice::Key a_key)
	{
		using Key = RE::BSWin32GamepadDevice::Key;

		uint32_t index;
		switch (a_key) {
			case Key::kUp:
				index = 0;
				break;
			case Key::kDown:
				index = 1;
				break;
			case Key::kLeft:
				index = 2;
				break;
			case Key::kRight:
				index = 3;
				break;
			case Key::kStart:
				index = 4;
				break;
			case Key::kBack:
				index = 5;
				break;
			case Key::kLeftThumb:
				index = 6;
				break;
			case Key::kRightThumb:
				index = 7;
				break;
			case Key::kLeftShoulder:
				index = 8;
				break;
			case Key::kRightShoulder:
				index = 9;
				break;
			case Key::kA:
				index = 10;
				break;
			case Key::kB:
				index = 11;
				break;
			case Key::kX:
				index = 12;
				break;
			case Key::kY:
				index = 13;
				break;
			case Key::kLeftTrigger:
				index = 14;
				break;
			case Key::kRightTrigger:
				index = 15;
				break;
			default:
				index = kInvalidButton;
				break;
		}

		return index != kInvalidButton ? index + kGamepadOffset : kInvalidButton;
	}
}
