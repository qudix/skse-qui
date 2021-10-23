#pragma once

namespace Event
{
	using EventResult = RE::BSEventNotifyControl;

	class InputHandler;

	class InputEvent : public RE::BSTEventSink<RE::InputEvent*>
	{
	public:
		InputEvent();

		static InputEvent* GetSingleton();

		virtual EventResult ProcessEvent(RE::InputEvent* const* a_event, RE::BSTEventSource<RE::InputEvent*>*);

	private:
		using EventType = RE::INPUT_EVENT_TYPE;
		using DeviceType = RE::INPUT_DEVICE;

		InputEvent(const InputEvent&) = delete;
		InputEvent(InputEvent&&) = delete;
		virtual ~InputEvent() = default;

		InputEvent& operator=(const InputEvent&) = delete;
		InputEvent& operator=(InputEvent&&) = delete;

		std::vector<std::unique_ptr<InputHandler>> _callbacks;
	};

	void Register();
}
