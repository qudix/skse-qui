#pragma once

#include "General/Singleton.hpp"

namespace Core::Event
{
    using EventResult = RE::BSEventNotifyControl;

    class IEventHandler;

    class EventManager final :
        public General::Singleton<EventManager>
    {
        using HandlerVector = std::vector<IEventHandler*>;

    public:
        void Register(IEventHandler* a_handler);

        HandlerVector& GetHandlers() { return _handlers; }

    private:
        HandlerVector _handlers;
    };

    class UIEvent final :
        public General::Singleton<UIEvent>,
        public RE::BSTEventSink<RE::MenuOpenCloseEvent>
    {
    public:
        EventResult ProcessEvent(const RE::MenuOpenCloseEvent* a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*) override;
    };

    class InputEvent final :
        public General::Singleton<InputEvent>,
        public RE::BSTEventSink<RE::InputEvent*>
    {
    public:
        EventResult ProcessEvent(RE::InputEvent* const* a_event, RE::BSTEventSource<RE::InputEvent*>*) override;
    };
}
