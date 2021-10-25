#include "Event/Event.h"

#include "Menus/PluginExplorer/PluginExplorerHandler.h"

namespace Event
{
	InputEvent::InputEvent()
	{
		_callbacks.push_back(std::make_shared<Menus::PluginExplorerHandler>());
	}

	EventResult InputEvent::ProcessEvent(RE::InputEvent* const* a_event, RE::BSTEventSource<RE::InputEvent*>*)
	{
		if (a_event) {
			auto intfcStr = RE::InterfaceStrings::GetSingleton();
			auto ui = RE::UI::GetSingleton();
			if (ui->IsMenuOpen(intfcStr->console))
				return EventResult::kContinue;

			auto controlMap = RE::ControlMap::GetSingleton();
			if (ui->GameIsPaused() || !controlMap->IsMovementControlsEnabled())
				return EventResult::kContinue;

			for (auto& callback : _callbacks) {
				callback->Handle(*a_event);
			}
		}

		return EventResult::kContinue;
	}

	MenuEvent::MenuEvent()
	{
		_callbacks.push_back(std::make_shared<Menus::PluginExplorerHandler>());
	}

	EventResult MenuEvent::ProcessEvent(const RE::MenuOpenCloseEvent* a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*)
	{
		if (a_event) {
			for (auto& callback : _callbacks) {
				callback->Handle(*a_event);
			}
		}

		return EventResult::kContinue;
	}

	void Register()
	{
		InputEvent::Register();
		MenuEvent::Register();
	}
}
