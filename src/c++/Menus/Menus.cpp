#include "Menus/Menus.h"
#include "Menus/PluginExplorer/PluginExplorer.h"
#include "Menus/PluginExplorer/PluginExplorerMenu.h"

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

	void Reset()
	{
		PluginExplorer::Reset();
	}
}
