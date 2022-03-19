#include "Core/Menu/MainMenu.hpp"

#include "Scaleform/System/Function.hpp"
#include "Scaleform/System/Logger.hpp"

#include "Core/Config.hpp"

namespace Core::Menu
{
	void MainMenuEx::ProcessEx(RE::GPtr<RE::GFxMovieView> a_movie)
	{
		RE::GFxValue root;
		if (!a_movie->GetVariable(&root, "_root")) {
			logger::warn("MainMenuEx: No _root");
			return;
		}

		RE::GFxValue menuHolder;
		if (!root.GetMember("MenuHolder", &menuHolder)) {
			logger::warn("MainMenuEx: No _root.MenuHolder");
			return;
		}

		RE::GFxValue menuMC;
		if (!menuHolder.GetMember("Menu_mc", &menuMC)) {
			logger::warn("MainMenuEx: No _root.MenuHolder.Menu_mc");
			return;
		}

		auto& config = Config::Get().MainMenu;
		if (!config.UI.Logo) {
			RE::GFxValue logoMC;
			if (menuMC.GetMember("Logo_mc", &logoMC)) {
				logoMC.SetMember("_y", RE::GFxValue{ 1000.0 });
			} else {
				logger::warn("MainMenuEx: No _root.MenuHolder.Menu_mc.Logo_mc");
			}
		}

		if (!config.UI.Motd) {
			RE::GFxValue motdMC;
			if (menuMC.GetMember("MessageOfTheDay_mc", &motdMC)) {
				motdMC.SetMember("_y", RE::GFxValue{ 1000.0 });
			} else {
				logger::warn("MainMenuEx: No _root.MenuHolder.Menu_mc.MessageOfTheDay_mc");
			}
		}

		RE::GFxValue mainList;
		if (menuMC.GetMember("MainList", &mainList)) {
			RE::GFxValue entryList;
			if (mainList.Invoke("__get__entryList", &entryList)) {
				using element_t = std::pair<bool, std::string_view>;
				std::array values{
					element_t{ config.List.CC, "$CREATION CLUB" },
					element_t{ config.List.DLC, "$DOWNLOADABLE CONTENT" },
					element_t{ config.List.Mods, "$MOD MANAGER" },
					element_t{ config.List.Credits, "$CREDITS" },
					element_t{ config.List.Help, "$HELP" },
				};

				const auto size = entryList.GetArraySize();
				for (uint32_t i = size; i > 0; i--) {
					RE::GFxValue entry;
					if (!entryList.GetElement(i - 1, &entry))
						continue;

					RE::GFxValue entryText;
					if (!entry.GetMember("text", &entryText))
						continue;

					const std::string text = entryText.GetString();
					if (text.empty())
						continue;

					for (const auto& [enabled, name] : values) {
						if (!enabled && (text == name)) {
							entryList.RemoveElement(i - 1);
						}
					}
				}

				mainList.Invoke("InvalidateData");
			} else {
				logger::warn("MainMenuEx: Could not invoke _root.MenuHolder.Menu_mc.MainList.__get__entryList()");
			}
		} else {
			logger::warn("MainMenuEx: No _root.MenuHolder.Menu_mc.MainList");
		}

#ifdef SKYRIM_SUPPORT_AE
		if (!config.UI.Banner) {
			RE::GFxValue sky10;
			if (menuMC.GetMember("_Sky10UpSell", &sky10)) {
				sky10.SetMember("_y", RE::GFxValue{ 1000.0 });
			}

			RE::GFxValue sky10Text;
			if (menuMC.GetMember("_Sky10UpSellText", &sky10Text)) {
				sky10Text.SetMember("_y", RE::GFxValue{ 1000.0 });
			}

			RE::GFxValue sky10BG;
			if (menuMC.GetMember("_Sky10UpSellBG", &sky10BG)) {
				sky10BG.SetMember("_y", RE::GFxValue{ 1000.0 });
			}
		}
#endif
	}

	RE::UI_MESSAGE_RESULTS MainMenuEx::ProcessMessageEx(RE::UIMessage& a_message)
	{
		using Message = RE::UI_MESSAGE_TYPE;
		switch (a_message.type.get()) {
			case Message::kShow: {
				_show = true;
				break;
			}
			case Message::kUpdate: {
				if (_show) {
					_show = false;
					ProcessEx(uiMovie);
				}
				break;
			}
		}

		return _ProcessMessageFn(this, a_message);
	}

	void MainMenuEx::Install()
	{
		REL::Relocation<uintptr_t> vtbl(RE::VTABLE_MainMenu[0]);
		_ProcessMessageFn = vtbl.write_vfunc(0x4, &ProcessMessageEx);
	}
}
