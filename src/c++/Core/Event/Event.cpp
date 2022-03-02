#include "Core/Event/Event.hpp"
#include "Core/Event/EventHandler.hpp"

namespace Core::Event
{
	void EventManager::Register()
	{
		if (const auto ui = RE::UI::GetSingleton()) {
			logger::info("Sinking ui events...");
			ui->AddEventSink<RE::MenuOpenCloseEvent>(this);
		}

		if (const auto input = RE::BSInputDeviceManager::GetSingleton()) {
			logger::info("Sinking input events...");
			input->AddEventSink(this);
		}
	}

	void EventManager::Register(IEventHandler* a_handler)
	{
		_handlers.push_back(a_handler);
	}

	EventResult EventManager::ProcessEvent(const RE::MenuOpenCloseEvent* a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*)
	{
		if (!a_event)
			return EventResult::kContinue;

		for (auto& callback : _handlers) {
			callback->Handle(a_event);
		}

		return EventResult::kContinue;
	}

	EventResult EventManager::ProcessEvent(RE::InputEvent* const* a_event, RE::BSTEventSource<RE::InputEvent*>*)
	{
		if (!a_event)
			return EventResult::kContinue;

		for (auto& callback : _handlers) {
			callback->Handle(*a_event);
		}

		return EventResult::kContinue;
	}
}
