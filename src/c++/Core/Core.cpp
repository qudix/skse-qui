#include "Core/Core.hpp"
#include "Core/Config.hpp"

#include "Core/Event/Event.hpp"

#include "Core/Locale/LocaleManager.hpp"

#include "Core/Menu/PluginExplorer.hpp"
#include "Core/Menu/PluginExplorerHandler.hpp"
#include "Core/Menu/PluginExplorerMenu.hpp"

#include "Core/Menu/StartMenu.hpp"

namespace Core
{
	void OnDataLoaded()
	{
		Menu::PluginExplorer::Init();

		logger::info("Registering menus...");
		if (const auto ui = RE::UI::GetSingleton()) {
			ui->Register(Menu::PluginExplorerMenu::MENU_NAME, Menu::PluginExplorerMenu::Create);
		}

		logger::info("Registering event handlers...");
		if (const auto event = Event::EventManager::GetSingleton()) {
			event->Register();
			event->Register(Menu::PluginExplorerHandler::GetSingleton());
		}
	}

	void Init()
	{
		logger::info("Loading config...");
		if (const auto config = Config::GetSingleton()) {
			config->Load();
			config->Read();
		}

		logger::info("Loading localizations...");
		if (const auto locale = LocaleManager::GetSingleton()) {
			locale->SetLocale();
			locale->Load();
			locale->Dump();
		}

		logger::info("Registering scaleform...");
		if (const auto scaleform = SKSE::GetScaleformInterface()) {
			scaleform->Register([](RE::GFxMovieView* a_view, RE::GFxValue* a_root) -> bool {
				Menu::StartMenu::Register(a_view, a_root);
				return true;
			}, "QUI");
		}

		logger::info("Registering listener...");
		if (const auto messaging = SKSE::GetMessagingInterface()) {
			using Interface = SKSE::MessagingInterface;
			messaging->RegisterListener("SKSE", [](Interface::Message* a_msg) {
				switch (a_msg->type) {
					case Interface::kDataLoaded: OnDataLoaded(); break;
				}
			});
		}
	}
}
