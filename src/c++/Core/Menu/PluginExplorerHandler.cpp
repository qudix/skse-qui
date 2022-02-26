#include "Core/Menu/PluginExplorerHandler.hpp"
#include "Core/Menu/PluginExplorerMenu.hpp"
#include "Core/Menu/PluginExplorer.hpp"

#include "Core/Config.hpp"

namespace Core::Menu
{
    void PluginExplorerHandler::Handle(const RE::InputEvent* a_event)
    {
        auto intfcStr = RE::InterfaceStrings::GetSingleton();
        auto ui = RE::UI::GetSingleton();
        if (ui->IsMenuOpen(intfcStr->console))
            return;

        auto controlMap = RE::ControlMap::GetSingleton();
        if (ui->GameIsPaused() || !controlMap->IsMovementControlsEnabled())
            return;

        using InputDevice = RE::INPUT_DEVICE;
        for (auto iter = a_event; iter; iter = iter->next) {
            auto event = iter->AsButtonEvent();
            if (!event)
                continue;

            if (!event->IsDown())
                continue;

            auto device = event->GetDevice();
            switch (device) {
            case InputDevice::kGamepad:
                //ProcessGamepad(*event);
                break;
            case InputDevice::kKeyboard:
                ProcessKeyboard(*event);
                break;
            }
        }
    }

    void PluginExplorerHandler::Handle(const RE::MenuOpenCloseEvent* a_event)
    {
        using Menu = PluginExplorerMenu;
        auto uiStr = RE::InterfaceStrings::GetSingleton();
        if (!uiStr)
            return;

        auto& config = Config::Get();
        auto& name = a_event->menuName;
        if (name == uiStr->containerMenu) {
            if (!a_event->opening) {
                bool loop = config.PluginExplorer.Loop;
                auto focus = Menu::GetFocus();
                if (loop && focus == Menu::Focus::Container) {
                    Menu::SetFocus(Menu::Focus::ContainerLoop);
                    Menu::Open();
                }
            }
        } else if (name == Menu::MENU_NAME) {
            if (!a_event->opening) {
                auto focus = Menu::GetFocus();
                if (focus != Menu::Focus::Container)
                    return;

                auto pluginName = Menu::GetPluginName();
                auto pluginIndex = Menu::GetPluginIndex();
                if (pluginName.empty())
                    return;

                auto formName = Menu::GetFormName();
                auto formType = Menu::GetFormType();
                if (formType != RE::FormType::None) {
                    bool success = PluginExplorer::OpenContainer(pluginIndex, formType);
                    if (!success) {
                        logger::info("Failed to open container: [{}] {} ({})",
                            pluginIndex, pluginName, formName);
                    }
                }
            }
        }
    }

    void PluginExplorerHandler::ProcessKeyboard(const RE::ButtonEvent& a_event)
    {
        using Menu = PluginExplorerMenu;
        auto& config = Config::Get();
        auto& key = config.PluginExplorer.Key;
        auto id = a_event.GetIDCode();
        if (id == key.KeyboardToggle) {
            Menu::Toggle();
        }
    }
}
