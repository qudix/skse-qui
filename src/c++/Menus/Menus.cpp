#include "Menus/Menus.h"

#include "Menus/PluginExplorer/PluginExplorer.h"
#include "Menus/PluginExplorer/PluginExplorerMenu.h"

#include "Menus/Start/Start.h"

namespace Menus
{
	void Register()
	{
		if (const auto ui = RE::UI::GetSingleton()) {
			ui->Register(PluginExplorerMenu::MENU_NAME, PluginExplorerMenu::Create);
			logger::info("Registered Menus");
		}

		PluginExplorer::Init();
	}

	void Load()
	{
		if (const auto scaleform = SKSE::GetScaleformInterface()) {
			scaleform->Register([](RE::GFxMovieView* a_view, RE::GFxValue* a_root) -> bool {
				Start::Register(a_view, a_root);
				return true;
			}, "QUI");
		}
	}

	void Reset()
	{
		PluginExplorer::Reset();
	}
}
