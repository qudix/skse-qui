#pragma once

#include "Scaleform/Object.hpp"
#include "Scaleform/Array.hpp"
#include "Scaleform/TextField.hpp"
#include "Scaleform/CLIK/GFx/Controls/ButtonBar.hpp"
#include "Scaleform/Common/ItemList.hpp"

namespace Core::Menu
{
	class PluginExplorerMenu :
		public RE::IMenu,
		public RE::MenuEventHandler
	{
	public:
		using Super = RE::IMenu;
		using GRefCountBaseStatImpl::operator new;
		using GRefCountBaseStatImpl::operator delete;

	public:
		static constexpr std::string_view FILE_NAME{ "PluginExplorerMenu" };
		static constexpr std::string_view MENU_NAME{ "PluginExplorerMenu" };
		static constexpr std::int8_t SORT_PRIORITY{ 3 };

		PluginExplorerMenu();
		~PluginExplorerMenu() override;

		static RE::IMenu* Create() { return new PluginExplorerMenu(); }

		// override (IMenu)
		RE::UI_MESSAGE_RESULTS ProcessMessage(RE::UIMessage& a_message) override;
		void AdvanceMovie(float a_interval, uint32_t a_currentTime) override;
		void RefreshPlatform() override { UpdateButtonBar(); }

		// override (MenuEventHandler)
		bool CanProcess(RE::InputEvent* a_event) override;
		bool ProcessButton(RE::ButtonEvent* a_event) override;

	public:
		enum class Focus
		{
			Plugin,
			Form,
			Container,
			ContainerLoop,
			Search
		};

	public:
		static bool IsOpen();

		static void Open();
		static void Close();
		static void Toggle();

		static void SetFocus(Focus a_focus) { _focus = a_focus; }
		static Focus GetFocus() { return _focus; };

		static std::string GetPluginName() { return _pluginName; }
		static uint32_t GetPluginIndex() { return _pluginIndex; }

		static std::string GetFormName() { return _formName; }
		static RE::FormType GetFormType() { return _formType; }

	private:
		void Init();
		void InitExtensions();

		void OnOpen();
		void OnClose();

		void Refresh();
		void RefreshPlugins();
		void RefreshForms();
		void RefreshUI();

		void ModSelectedIndex(double a_mod);
		void ModSelectedPage(double a_mod);

		void Select();
		void Back();
		void Search();

		void UpdatePosition();
		void UpdateTitle();
		void UpdateButtonBar();
		void UpdateSearchField();

	private:
		RE::GPtr<RE::GFxMovieView> _view;

		SF::MovieClip _rootObj;
		SF::TextField _title;

		SF::ItemList _pluginList;
		SF::ItemList _formList;

		SF::CLIK::GFx::Controls::ButtonBar _buttonBar;
		RE::GFxValue _buttonBarProvider;

		SF::MovieClip _searchField;
		SF::TextField _searchText;

		uint32_t _heldGuard{ 0 };
		uint32_t _heldCount{ 0 };
		uint32_t _upHeld{ 0 };
		uint32_t _downHeld{ 0 };

		bool _autoSearch{ false };
		bool _shiftHeld{ false };

		static inline Focus _focus{ Focus::Plugin };

		static inline std::string _pluginName;
		static inline uint32_t _pluginIndex{ 0 };
		static inline double _pluginListIndex{ 0 };

		static inline std::string _formName;
		static inline RE::FormType _formType{ RE::FormType::None };
		static inline double _formListIndex{ 0 };

		static inline std::string _searchTerm;
	};
}
