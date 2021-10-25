#pragma once

#include "Event/EventHandler.h"

namespace Menus
{
	class PluginExplorerHandler :
		public Event::InputEventHandler,
		public Event::MenuEventHandler
	{
	public:
		PluginExplorerHandler() = default;

		void Handle(RE::InputEvent* const& a_event) override;
		void Handle(const RE::MenuOpenCloseEvent& a_event) override;

	private:
		void ProcessKeyboard(const RE::ButtonEvent& a_event);
		//void ProcessGamepad(const RE::ButtonEvent& a_event);
	};
}
