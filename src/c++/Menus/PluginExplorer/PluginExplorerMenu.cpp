#include "Menus/PluginExplorer/PluginExplorerMenu.h"
#include "Menus/PluginExplorer/PluginExplorer.h"
#include "Menus/PluginExplorer/Items/ItemForm.h"
#include "Menus/PluginExplorer/Items/ItemPlugin.h"

#include "Event/Input/Input.h"
#include "Scaleform/System/Logger.h"

namespace Menus
{
	PluginExplorerMenu::PluginExplorerMenu() :
		Super(),
		RE::MenuEventHandler()
	{
		auto menu = static_cast<Super*>(this);
		menu->depthPriority = -1;
		menu->menuFlags.set(
			Flag::kDisablePauseMenu,
			Flag::kTopmostRenderedMenu,
			Flag::kAllowSaving,
			Flag::kHasButtonBar,
			Flag::kUsesMovementToDirection
		);
		menu->inputContext = Context::kFavor;

		auto scaleform = RE::BSScaleformManager::GetSingleton();
		bool success = scaleform->LoadMovieEx(menu, FILE_NAME, [](RE::GFxMovieDef* a_def) -> void {
			a_def->SetState(
				RE::GFxState::StateType::kLog,
				RE::make_gptr<Scaleform::Logger<PluginExplorerMenu>>().get());
		});

		if (!success) {
			logger::critical("{} did not have a view due to missing dependencies! Aborting process!", MENU_NAME);
			assert(success);
		}

		_view = menu->uiMovie;
		_view->SetMouseCursorCount(0);

		Init();
		InitExtensions();

		auto mc = RE::MenuControls::GetSingleton();
		mc->RegisterHandler(this);
	}

	PluginExplorerMenu::~PluginExplorerMenu()
	{
		auto mc = RE::MenuControls::GetSingleton();
		mc->RemoveHandler(this);
	}

	auto PluginExplorerMenu::ProcessMessage(RE::UIMessage& a_message)
		-> RE::UI_MESSAGE_RESULTS
	{
		using Message = RE::UI_MESSAGE_TYPE;
		using Result = RE::UI_MESSAGE_RESULTS;
		switch (*a_message.type) {
			case Message::kShow:
				OnOpen();
				return Result::kHandled;
			case Message::kHide:
			case Message::kForceHide:
				OnClose();
				return Result::kHandled;
			case Message::kUpdateController:
				RefreshPlatform();
				return Result::kPassOn;
			default:
				return Super::ProcessMessage(a_message);
		}
	}

	bool PluginExplorerMenu::CanProcess(RE::InputEvent* a_event)
	{
		using Type = RE::INPUT_EVENT_TYPE;

		if (!a_event)
			return false;

		if (!a_event->eventType.all(Type::kButton))
			return false;

		return true;
	}

	bool PluginExplorerMenu::ProcessButton(RE::ButtonEvent* a_event)
	{
		using Device = RE::INPUT_DEVICE;
		if (!a_event->IsDown())
			return true;

		switch (a_event->GetDevice()) {
		case Device::kKeyboard:
			{
				using Key = RE::BSWin32KeyboardDevice::Key;
				switch (a_event->idCode) {
				case Key::kEnter:
					Select();
					break;
				case Key::kEscape:
					Back();
					break;
				case Key::kW:
					ModSelectedIndex(-1);
					break;
				case Key::kS:
					ModSelectedIndex(1);
					break;
				}
			}
			break;
		case Device::kMouse:
			{
				using Key = RE::BSWin32MouseDevice::Key;
				switch (a_event->idCode) {
				case Key::kLeftButton:
					Select();
					break;
				case Key::kRightButton:
					Back();
					break;
				case Key::kWheelUp:
					ModSelectedIndex(-1);
					break;
				case Key::kWheelDown:
					ModSelectedIndex(1);
					break;
				}
			}
			break;
		case Device::kGamepad:
			{
				using Key = RE::BSWin32GamepadDevice::Key;
				switch (a_event->idCode) {
				case Key::kA:
					Select();
					break;
				case Key::kBack:
					Back();
					break;
				case Key::kUp:
					ModSelectedIndex(-1);
					break;
				case Key::kDown:
					ModSelectedIndex(1);
					break;
				}
			}
			break;
		}

		return true;
	}

	bool PluginExplorerMenu::IsOpen()
	{
		auto ui = RE::UI::GetSingleton();
		return ui->IsMenuOpen(MENU_NAME);
	}

	void PluginExplorerMenu::Open()
	{
		auto queue = RE::UIMessageQueue::GetSingleton();
		queue->AddMessage(MENU_NAME, RE::UI_MESSAGE_TYPE::kShow, nullptr);
	}

	void PluginExplorerMenu::Close()
	{
		auto queue = RE::UIMessageQueue::GetSingleton();
		queue->AddMessage(MENU_NAME, RE::UI_MESSAGE_TYPE::kHide, nullptr);
	}

	void PluginExplorerMenu::Toggle()
	{
		if (IsOpen())
			Close();
		else
			Open();
	}

	void PluginExplorerMenu::Init()
	{
		using element_t = std::pair<std::reference_wrapper<CLIK::Object>, std::string_view>;
		std::array objects{
			element_t{ std::ref(_rootObj), "_root.rootObj"sv },
			element_t{ std::ref(_title), "_root.rootObj.title"sv },
			element_t{ std::ref(_pluginList), "_root.rootObj.itemList"sv },
			element_t{ std::ref(_formList), "_root.rootObj.formList"sv },
			element_t{ std::ref(_buttonBar), "_root.rootObj.buttonBar"sv }
		};

		for (const auto& [object, path] : objects) {
			auto& instance = object.get().GetInstance();
			[[maybe_unused]] const bool success = _view->GetVariable(std::addressof(instance), path.data());
			assert(success && instance.IsObject());
		}

		_rootObj.Visible(true);

		_title.AutoSize(CLIK::Object{ "left" });
		_title.Visible(false);

		_pluginList.Init(_view);
		_formList.Init(_view);

		_view->CreateArray(std::addressof(_buttonBarProvider));
		_buttonBar.DataProvider(CLIK::Array{ _buttonBarProvider });

		UpdatePosition();
		RefreshPlugins();
		RefreshUI();
	}

	void PluginExplorerMenu::InitExtensions()
	{
		const RE::GFxValue boolean{ true };
		[[maybe_unused]] bool success;
		success = _view->SetVariable("_global.gfxExtensions", boolean);
		assert(success);
		success = _view->SetVariable("_global.noInvisibleAdvance", boolean);
		assert(success);
	}

	void PluginExplorerMenu::OnOpen()
	{
		using UEFlag = RE::ControlMap::UEFlag;
		auto controlMap = RE::ControlMap::GetSingleton();
		if (controlMap) {
			controlMap->ToggleControls(UEFlag::kMovement, false);
			controlMap->ToggleControls(UEFlag::kLooking, false);
			controlMap->ToggleControls(UEFlag::kPOVSwitch, false);
		}
	}

	void PluginExplorerMenu::OnClose()
	{
		using UEFlag = RE::ControlMap::UEFlag;
		auto controlMap = RE::ControlMap::GetSingleton();
		if (controlMap) {
			controlMap->ToggleControls(UEFlag::kMovement, true);
			controlMap->ToggleControls(UEFlag::kLooking, true);
			controlMap->ToggleControls(UEFlag::kPOVSwitch, true);
		}
	}

	void PluginExplorerMenu::RefreshPlugins()
	{
		const auto idx = static_cast<ptrdiff_t>(_pluginList.SelectedIndex());
		_pluginList.Clear();

		auto& plugins = PluginExplorer::GetPlugins();
		for (auto& [index, plugin] : plugins) {
			if (plugin.GetCount() == 0)
				continue;

			Item::ItemPlugin itemPlugin{ index, plugin.GetName(), plugin.GetCount() };
			_pluginList.PushBack(itemPlugin);
		}

		_pluginList.Refresh();
		_pluginList.RestoreIndex(idx);
	}

	void PluginExplorerMenu::RefreshForms()
	{
		if (_pluginName.empty())
			return;

		const auto idx = static_cast<ptrdiff_t>(_formList.SelectedIndex());
		_formList.Clear();

		auto plugin = PluginExplorer::FindPlugin(_pluginIndex);
		if (plugin) {
			for (auto& [type, map] : plugin->GetForms()) {
				Item::ItemForm form{ type, map.size() };
				_formList.PushBack(form);
			}
		}

		_formList.Refresh();
		_formList.RestoreIndex(idx);
		_formList.Visible(true);
	}

	void PluginExplorerMenu::RefreshUI()
	{
		UpdateTitle();
		UpdateButtonBar();
	}

	void PluginExplorerMenu::ModSelectedIndex(double a_mod)
	{
		if (_focus == Focus::Plugin) {
			_pluginList.ModSelectedIndex(a_mod);
		} else if (_focus == Focus::Form) {
			_formList.ModSelectedIndex(a_mod);
		}
	}

	void PluginExplorerMenu::ModSelectedPage(double a_mod)
	{
		std::array<RE::GFxValue, 1> args{ a_mod };
		if (_focus == Focus::Plugin)
			_pluginList.GetInstance().Invoke("modSelectedPage", args);
		else if (_focus == Focus::Form)
			_formList.GetInstance().Invoke("modSelectedPage", args);
	}

	void PluginExplorerMenu::Select()
	{
		if (_focus == Focus::Plugin) {
			auto plugin = _pluginList.SelectedItem();
			if (plugin) {
				_focus = Focus::Form;
				_pluginName = plugin->GetName();
				_pluginIndex = plugin->GetIndex();
				_pluginList.Visible(false);
				RefreshForms();
			}
		} else if (_focus == Focus::Form) {
			auto form = _formList.SelectedItem();
			if (form) {
				Close();
				// TODO: Create container with selected items and open with container UI
			}
		}

		RefreshUI();
	}

	void PluginExplorerMenu::Back()
	{
		if (_focus == Focus::Plugin) {
			Close();
		} else if (_focus == Focus::Form) {
			_focus = Focus::Plugin;
			_formList.Visible(false);
			_formList.SelectedIndex(0);
			_pluginList.Visible(true);
			_pluginName.clear();
			_pluginIndex = 0;
		}

		RefreshUI();
	}

	void PluginExplorerMenu::UpdatePosition()
	{
		auto def = _view->GetMovieDef();
		if (def) {
			//_rootObj.X(
			//	_rootObj.X() + def->GetWidth() / 5);
		}
	}

	void PluginExplorerMenu::UpdateTitle()
	{
		auto str = stl::safe_string("Plugins");	 //TODO: Localization?
		if (_focus == Focus::Form) {
			str = _pluginName;
		}
		_title.HTMLText(str);
		_title.Visible(true);
	}

	void PluginExplorerMenu::UpdateButtonBar()
	{
		if (!_view)
			return;

		uint32_t indexAccept;
		uint32_t indexCancel;

		auto input = RE::BSInputDeviceManager::GetSingleton();
		if (input->IsGamepadEnabled()) {
			using Key = RE::BSWin32GamepadDevice::Key;
			indexAccept = Input::GetGamepadIndex(Key::kA);
			indexCancel = Input::GetGamepadIndex(Key::kBack);
		} else {
			indexAccept = Input::kEnter;
			indexCancel = Input::kESC;
		}

		_buttonBarProvider.ClearElements();
		auto gmst = RE::GameSettingCollection::GetSingleton();
		auto makeButton = [&](uint32_t a_index, const char* a_label) {
			RE::GFxValue obj;
			_view->CreateObject(std::addressof(obj));
			auto setting = gmst->GetSetting(a_label);
			obj.SetMember("label", { static_cast<std::string_view>(setting->GetString()) });
			obj.SetMember("index", { a_index });
			_buttonBarProvider.PushBack(obj);
		};

		makeButton(indexAccept, "sAccept");
		if (_focus == Focus::Plugin)
			makeButton(indexCancel, "sCancel");
		else
			makeButton(indexCancel, "sBack");

		_buttonBar.InvalidateData();
	}
}
