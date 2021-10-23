#pragma once

namespace Event
{
	class InputHandler
	{
	public:
		virtual ~InputHandler() = default;

		virtual void Handle(RE::InputEvent* const& a_event) = 0;
	};
}
