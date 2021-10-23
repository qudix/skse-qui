#include "Event/Event.h"
#include "Event/Input/InputHandler.h"

namespace Event
{
	InputEvent::InputEvent()
	{
		_callbacks.push_back(std::make_unique<KeyHandler>());
	}

	InputEvent* InputEvent::GetSingleton()
	{
		static InputEvent singleton;
		return std::addressof(singleton);
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

	void Register()
	{
		auto input = RE::BSInputDeviceManager::GetSingleton();
		input->AddEventSink(InputEvent::GetSingleton());
	}
}
