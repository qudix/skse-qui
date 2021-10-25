#pragma once

namespace Event
{
	class InputEventHandler
	{
	public:
		virtual ~InputEventHandler() = default;

		virtual void Handle(RE::InputEvent* const& a_event) = 0;
	};

	class MenuEventHandler
	{
	public:
		virtual ~MenuEventHandler() = default;

		virtual void Handle(const RE::MenuOpenCloseEvent& a_event) = 0;
	};
}
