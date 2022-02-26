#include "Core/Core.hpp"
#include "Core/Config.hpp"

#include "Core/Event/Event.hpp"

#include "Core/Menu/PluginExplorer.hpp"
#include "Core/Menu/PluginExplorerHandler.hpp"
#include "Core/Menu/PluginExplorerMenu.hpp"

#include "Core/Menu/StartMenu.hpp"

namespace Core
{
    void OnDataLoaded()
    {
        Menu::PluginExplorer::Init();

        if (const auto ui = RE::UI::GetSingleton()) {
            logger::info("Registering menus...");
            ui->Register(Menu::PluginExplorerMenu::MENU_NAME, Menu::PluginExplorerMenu::Create);
            logger::info("Sinking ui events...");
            ui->AddEventSink(Event::UIEvent::GetSingleton());
        }

        if (const auto input = RE::BSInputDeviceManager::GetSingleton()) {
            logger::info("Sinking input events...");
            input->AddEventSink(Event::InputEvent::GetSingleton());
        }

        if (const auto event = Event::EventManager::GetSingleton()) {
            logger::info("Registering event handlers...");
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
                case Interface::kDataLoaded: 
                    OnDataLoaded();
                    break;
                }
            });
        }
    }
}
