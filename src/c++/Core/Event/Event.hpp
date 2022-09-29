#pragma once

#include "General/Singleton.hpp"

namespace Core
{
	class IEventHandler;
}

namespace Core::Event
{
	using EventResult = RE::BSEventNotifyControl;

	class EventManager final :
		public ISingleton<EventManager>,
		public RE::BSTEventSink<RE::MenuOpenCloseEvent>,
		public RE::BSTEventSink<RE::InputEvent*>
	{
		using HandlerVector = std::vector<IEventHandler*>;

	public:
		void Register();
		void Register(IEventHandler* a_handler);

	public:	 // BSTEventSink
		EventResult ProcessEvent(const RE::MenuOpenCloseEvent* a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*) override;

		EventResult ProcessEvent(RE::InputEvent* const* a_event, RE::BSTEventSource<RE::InputEvent*>*) override;

	private:
		HandlerVector _handlers;
	};
}
