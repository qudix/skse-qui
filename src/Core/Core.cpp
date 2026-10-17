#include "Core/Core.hpp"
#include "Core/Config.hpp"

#include "Core/Console/ConsoleCommands.hpp"

#include "Core/Event/Event.hpp"

#include "Core/Locale/LocaleManager.hpp"

#include "Core/Menu/JournalMenu.hpp"
#include "Core/Menu/MainMenu.hpp"
#include "Core/Menu/PluginExplorer.hpp"
#include "Core/Menu/PluginExplorerHandler.hpp"
#include "Core/Menu/PluginExplorerMenu.hpp"

namespace Core
{
	void OnDataLoaded()
	{
		auto& config = Config::Get();
		if (config.PluginExplorer.Enable)
			Menu::PluginExplorer::Init();

		REX::INFO("Registering console commands...");
		ConsoleCommand::Register();

		REX::INFO("Registering menus...");
		if (const auto ui = RE::UI::GetSingleton()) {
			if (config.PluginExplorer.Enable)
				ui->Register(Menu::PluginExplorerMenu::MENU_NAME, Menu::PluginExplorerMenu::Create);
		}

		REX::INFO("Registering event handlers...");
		if (const auto event = Event::EventManager::GetSingleton()) {
			event->Register();
			if (config.PluginExplorer.Enable)
				event->Register(Menu::PluginExplorerHandler::GetSingleton());
		}
	}

	void Init()
	{
		REX::INFO("Loading config...");
		if (const auto config = Config::GetSingleton()) {
			config->Load();
			config->Read();
		}

		REX::INFO("Loading localizations...");
		auto& config = Config::Get();
		if (const auto locale = LocaleManager::GetSingleton()) {
			locale->SetLocale(config.General.Locale);
			locale->Load();
			//locale->Dump();
		}

		REX::INFO("Installing hooks...");
		if (config.JournalMenu.Enable)
			Menu::JournalMenuEx::Install();

		if (config.MainMenu.Enable)
			Menu::MainMenuEx::Install();

		REX::INFO("Registering listener...");
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
