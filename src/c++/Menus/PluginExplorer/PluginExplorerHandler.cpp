#include "Menus/PluginExplorer/PluginExplorerHandler.h"
#include "Menus/PluginExplorer/PluginExplorerMenu.h"

namespace Menus
{
	void PluginExplorerHandler::Handle(RE::InputEvent* const& a_event)
	{
		using InputDevice = RE::INPUT_DEVICE;
		for (auto iter = a_event; iter; iter = iter->next) {
			auto event = iter->AsButtonEvent();
			if (!event)
				continue;

			if (!event->IsDown())
				continue;

			auto device = event->GetDevice();
			switch (device) {
			case InputDevice::kGamepad:
				//ProcessGamepad(*event);
				break;
			case InputDevice::kKeyboard:
				ProcessKeyboard(*event);
				break;
			}
		}
	}

	void PluginExplorerHandler::Handle(const RE::MenuOpenCloseEvent& a_event)
	{
		using Menu = Menus::PluginExplorerMenu;
		auto uiStr = RE::InterfaceStrings::GetSingleton();
		if (!uiStr)
			return;

		auto& name = a_event.menuName;
		if (name == uiStr->containerMenu) {
			if (!a_event.opening) {
				bool loop = Settings::PluginExplorer.Loop;
				auto focus = Menu::GetFocus();
				if (loop && focus == Menu::Focus::Container)
					Menu::Open();
			}
		}
	}

	void PluginExplorerHandler::ProcessKeyboard(const RE::ButtonEvent& a_event)
	{
		using Menu = Menus::PluginExplorerMenu;
		auto& key = Settings::PluginExplorer.Key;
		auto id = a_event.GetIDCode();
		if (id == key.KeyboardToggle) {
			Menu::Toggle();
		}
	}
}
