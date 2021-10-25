#pragma once

namespace Event
{
	using EventResult = RE::BSEventNotifyControl;

	class InputEventHandler;
	class MenuEventHandler;

	class InputEvent final :
		public RE::BSTEventSink<RE::InputEvent*>
	{
	public:
		InputEvent();

		static InputEvent* GetSingleton()
		{
			static InputEvent singleton;
			return std::addressof(singleton);
		}

		static void Register()
		{
			auto input = RE::BSInputDeviceManager::GetSingleton();
			if (input) {
				input->AddEventSink(InputEvent::GetSingleton());
			}
		}

		virtual EventResult ProcessEvent(RE::InputEvent* const* a_event, RE::BSTEventSource<RE::InputEvent*>*);

	private:
		using EventType = RE::INPUT_EVENT_TYPE;
		using DeviceType = RE::INPUT_DEVICE;

		InputEvent(const InputEvent&) = delete;
		InputEvent(InputEvent&&) = delete;
		virtual ~InputEvent() = default;

		InputEvent& operator=(const InputEvent&) = delete;
		InputEvent& operator=(InputEvent&&) = delete;

		std::vector<std::shared_ptr<InputEventHandler>> _callbacks;
	};

	class MenuEvent final :
		public RE::BSTEventSink<RE::MenuOpenCloseEvent>
	{
	public:
		MenuEvent();

		static MenuEvent* GetSingleton()
		{
			static MenuEvent singleton;
			return std::addressof(singleton);
		}

		static void Register()
		{
			auto ui = RE::UI::GetSingleton();
			if (ui) {
				ui->AddEventSink(MenuEvent::GetSingleton());
			}
		}

		virtual EventResult ProcessEvent(const RE::MenuOpenCloseEvent* a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*);

	private:
		MenuEvent(const MenuEvent&) = delete;
		MenuEvent(MenuEvent&&) = delete;
		virtual ~MenuEvent() = default;

		MenuEvent& operator=(const MenuEvent&) = delete;
		MenuEvent& operator=(MenuEvent&&) = delete;

		std::vector<std::shared_ptr<MenuEventHandler>> _callbacks;
	};

	void Register();
}
