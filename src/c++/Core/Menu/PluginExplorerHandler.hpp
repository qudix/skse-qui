#pragma once

#include "Core/Event/EventHandler.hpp"

#include "General/Singleton.hpp"

namespace Core::Menu
{
	class PluginExplorerHandler final :
		public ISingleton<PluginExplorerHandler>,
		public IEventHandler
	{
	public:
		PluginExplorerHandler() = default;

	public:	 // IEventHandler
		// UI
		void Handle(const RE::MenuOpenCloseEvent* a_event) override;

		// Input
		void Handle(const RE::InputEvent* a_event) override;

	private:
		void ProcessKeyboard(const RE::ButtonEvent& a_event);
		//void ProcessGamepad(const RE::ButtonEvent& a_event);
	};
}
