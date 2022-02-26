#include "Core/Event/Event.hpp"
#include "Core/Event/EventHandler.hpp"

namespace Core::Event
{
	void EventManager::Register(IEventHandler* a_handler)
	{
		_handlers.push_back(a_handler);
	}

	EventResult UIEvent::ProcessEvent(const RE::MenuOpenCloseEvent* a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*)
	{
		if (!a_event)
			return EventResult::kContinue;

		auto manager = EventManager::GetSingleton();
		for (auto& callback : manager->GetHandlers()) {
			callback->Handle(a_event);
		}

		return EventResult::kContinue;
	}

	EventResult InputEvent::ProcessEvent(RE::InputEvent* const* a_event, RE::BSTEventSource<RE::InputEvent*>*)
	{
		if (!a_event)
			return EventResult::kContinue;

		auto manager = EventManager::GetSingleton();
		for (auto& callback : manager->GetHandlers()) {
			callback->Handle(*a_event);
		}

		return EventResult::kContinue;
	}
}
