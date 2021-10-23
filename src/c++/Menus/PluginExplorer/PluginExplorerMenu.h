#pragma once

#include "Scaleform/CLIK/Array.h"
#include "Scaleform/CLIK/TextField.h"
#include "Scaleform/CLIK/GFx/Controls/ButtonBar.h"
#include "Scaleform/Common/ItemList.h"

namespace Menus
{
	namespace Item
	{
		struct ItemPlugin;
		struct ItemForm;
	}

	class PluginExplorerMenu :
		public RE::IMenu,
		public RE::MenuEventHandler
	{
	public:
		using Super = RE::IMenu;
		using GRefCountBaseStatImpl::operator new;
		using GRefCountBaseStatImpl::operator delete;

	public:
		static constexpr std::string_view FILE_NAME{ "QUI/PluginExplorerMenu" };
		static constexpr std::string_view MENU_NAME{ "PluginExplorerMenu" };
		static constexpr std::int8_t SORT_PRIORITY{ 3 };

		PluginExplorerMenu();
		~PluginExplorerMenu() override;

		static RE::IMenu* Create() { return new PluginExplorerMenu(); }

		// override (IMenu)
		RE::UI_MESSAGE_RESULTS	ProcessMessage(RE::UIMessage& a_message) override;
		void					RefreshPlatform() override { UpdateButtonBar(); }

		// override (MenuEventHandler)
		bool CanProcess(RE::InputEvent* a_event) override;
		bool ProcessButton(RE::ButtonEvent* a_event) override;

		void InitExtensions();

	public:
		static bool IsOpen();

		static void Open();
		static void Close();
		static void Toggle();

	private:
		enum class Focus
		{
			Plugin,
			Form
		};

		void Init();
		void OnOpen();
		void OnClose();

		void RefreshPlugins();
		void RefreshForms();
		void RefreshUI();

		void ModSelectedIndex(double a_mod);
		void ModSelectedPage(double a_mod);

		void Select();
		void Back();

		void UpdatePosition();
		void UpdateTitle();
		void UpdateButtonBar();

	private:
		RE::GPtr<RE::GFxMovieView> _view;

		CLIK::MovieClip _rootObj;
		CLIK::TextField _title;

		Scaleform::ItemList<Item::ItemPlugin> _pluginList;
		Scaleform::ItemList<Item::ItemForm> _formList;

		CLIK::GFx::Controls::ButtonBar _buttonBar;
		RE::GFxValue _buttonBarProvider;

		Focus _focus{ Focus::Plugin };
		std::string _pluginName;
		uint32_t _pluginFormID;
	};
}
