#include "Event/Input/InputHandler.h"
#include "Event/Input/Input.h"

#include "Menus/PluginExplorer/PluginExplorerMenu.h"

namespace Event
{
	void KeyHandler::Handle(RE::InputEvent* const& a_event)
	{
		for (auto iter = a_event; iter; iter = iter->next) {
			auto event = iter->AsButtonEvent();
			if (!event)
				continue;

			if (!event->IsDown())
				continue;

			auto device = event->GetDevice();
			switch (device) {
			case DeviceType::kGamepad:
				//ProcessGamepad(*event);
				break;
			case DeviceType::kKeyboard:
				ProcessKeyboard(*event);
				break;
			}
		}
	}

	RE::BSWin32KeyboardDevice::Key KeyHandler::AsKeyboardKey(int64_t a_key)
	{
		return static_cast<RE::BSWin32KeyboardDevice::Key>(a_key);
	}

	void KeyHandler::ProcessKeyboard(const RE::ButtonEvent& a_event)
	{
		auto key = a_event.GetIDCode();
		auto pluginExplorerKey = AsKeyboardKey(*Settings::PluginExplorerKey);
		if (key == pluginExplorerKey) {
			Menus::PluginExplorerMenu::Toggle();
			return;
		}
	}
}
