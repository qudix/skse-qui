#include "Core/Menu/PluginExplorerMenu.hpp"
#include "Core/Menu/PluginExplorer.hpp"
#include "Core/Menu/Items/ItemForm.hpp"
#include "Core/Menu/Items/ItemPlugin.hpp"

#include "Core/Config.hpp"
#include "Core/Locale/LocaleManager.hpp"

#include "General/Input.hpp"

#include "Scaleform/System/Logger.hpp"

namespace Core::Menu
{
	PluginExplorerMenu::PluginExplorerMenu() :
		Super(),
		RE::MenuEventHandler()
	{
		auto menu = static_cast<Super*>(this);
		menu->inputContext = Context::kItemMenu;
		menu->depthPriority = SORT_PRIORITY;
		menu->menuFlags.set(
			Flag::kUsesMenuContext,
			Flag::kDisablePauseMenu,
			Flag::kAllowSaving,
			Flag::kHasButtonBar,
			Flag::kUsesMovementToDirection);

		auto& config = Config::Get();
		if (config.PluginExplorer.Pause)
			menu->menuFlags.set(Flag::kPausesGame);

		auto scaleform = RE::BSScaleformManager::GetSingleton();
		bool success = scaleform->LoadMovieEx(menu, FILE_NAME, [](RE::GFxMovieDef* a_def) -> void {
			a_def->SetState(
				RE::GFxState::StateType::kLog,
				RE::make_gptr<Scaleform::Logger<PluginExplorerMenu>>().get());
		});

		if (!success) {
			auto message = fmt::format("{} did not have a view due to missing dependencies!\n", MENU_NAME);
			message += "SkyUI must be installed.";
			stl::report_and_fail(message);
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

	void PluginExplorerMenu::AdvanceMovie(float a_interval, uint32_t a_currentTime)
	{
		if ((_upHeld > 0) || (_downHeld > 0)) {
			_heldGuard += 1;
			if (_heldGuard >= 15) {
				_heldCount += 1;
				if (_heldCount >= 5) {
					if (_upHeld)
						ModSelectedIndex(-1);
					else if (_downHeld)
						ModSelectedIndex(1);

					_heldCount = 0;
				}
			}
		} else {
			_heldGuard = 0;
			_heldCount = 0;
		}

		Super::AdvanceMovie(a_interval, a_currentTime);
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
		auto device = a_event->GetDevice();

		if (a_event->IsUp()) {
			switch (device) {
				case Device::kKeyboard:
					{
						using Key = RE::BSWin32KeyboardDevice::Key;
						switch (a_event->idCode) {
							case Key::kW:
							case Key::kUp:
								{
									if (_upHeld > 0)
										_upHeld -= 1;
									break;
								}
							case Key::kS:
							case Key::kDown:
								{
									if (_downHeld > 0)
										_downHeld -= 1;
									break;
								}
						}
					}
					break;
				case Device::kGamepad:
					{
						using Key = RE::BSWin32GamepadDevice::Key;
						switch (a_event->idCode) {
							case Key::kUp:
								{
									if (_upHeld > 0)
										_upHeld -= 1;
									break;
								}
							case Key::kDown:
								{
									if (_downHeld > 0)
										_downHeld -= 1;
									break;
								}
						}
					}
			}
		}

		if (a_event->IsDown()) {
			switch (device) {
				case Device::kKeyboard:
					{
						using Key = RE::BSWin32KeyboardDevice::Key;
						switch (a_event->idCode) {
							case Key::kD:
							case Key::kRight:
							case Key::kEnter:
								Select();
								break;
							case Key::kA:
							case Key::kLeft:
							case Key::kEscape:
							case Key::kTab:
								Back();
								break;
							case Key::kW:
							case Key::kUp:
								{
									_upHeld += 1;
									ModSelectedIndex(-1);
									break;
								}
							case Key::kS:
							case Key::kDown:
								{
									_downHeld += 1;
									ModSelectedIndex(1);
									break;
								}
							case Key::kPageUp:
								ModSelectedIndex(-16);
								break;
							case Key::kPageDown:
								ModSelectedIndex(16);
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
							case Key::kB:
								Back();
								break;
							case Key::kUp:
								{
									_upHeld += 1;
									ModSelectedIndex(-1);
									break;
								}
							case Key::kDown:
								{
									_downHeld += 1;
									ModSelectedIndex(1);
									break;
								}
						}
					}
					break;
			}
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

		Refresh();

		auto container = PluginExplorer::GetContainer();
		if (container) {
			auto player = RE::PlayerCharacter::GetSingleton();
			container->SetParentCell(player->GetParentCell());
			container->SetPosition({ player->GetPositionX(), player->GetPositionY(), -2000 });
			container->SetCollision(false);
		} else {
			logger::critical("No container");
		}
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
		if (const auto control = RE::ControlMap::GetSingleton()) {
			control->ToggleControls(UEFlag::kPOVSwitch, false);
		}

		if (const auto queue = RE::UIMessageQueue::GetSingleton()) {
			queue->AddMessage(RE::HUDMenu::MENU_NAME, RE::UI_MESSAGE_TYPE::kHide, nullptr);
		}
	}

	void PluginExplorerMenu::OnClose()
	{
		using UEFlag = RE::ControlMap::UEFlag;
		if (const auto control = RE::ControlMap::GetSingleton()) {
			control->ToggleControls(UEFlag::kPOVSwitch, true);
		}

		if (const auto queue = RE::UIMessageQueue::GetSingleton()) {
			queue->AddMessage(RE::HUDMenu::MENU_NAME, RE::UI_MESSAGE_TYPE::kShow, nullptr);
		}
	}

	void PluginExplorerMenu::Refresh()
	{
		UpdatePosition();
		RefreshPlugins();

		if (_focus == Focus::ContainerLoop) {
			_focus = Focus::Form;
			_pluginList.RestoreIndex(_pluginListIndex);
			_pluginList.Visible(false);
			RefreshForms();
			_formList.RestoreIndex(_formListIndex);
		} else {
			_focus = Focus::Plugin;
			_pluginName = "";
			_pluginIndex = 0;
			_pluginListIndex = 0;
			_formName = "";
			_formType = RE::FormType::None;
			_formListIndex = 0;
		}

		RefreshUI();
	}

	void PluginExplorerMenu::RefreshPlugins()
	{
		const auto idx = _pluginList.SelectedIndex();
		_pluginList.clear();

		auto& plugins = PluginExplorer::GetPlugins();
		for (auto& [index, plugin] : plugins) {
			if (plugin.GetCount() == 0)
				continue;

			Item::ItemPlugin itemPlugin{ index, plugin.GetName(), plugin.GetCount() };
			_pluginList.push_back(itemPlugin);
		}

		_pluginList.Refresh();
		_pluginList.RestoreIndex(idx);
	}

	void PluginExplorerMenu::RefreshForms()
	{
		if (_pluginName.empty())
			return;

		const auto idx = _formList.SelectedIndex();
		_formList.clear();

		auto plugin = PluginExplorer::FindPlugin(_pluginIndex);
		if (plugin) {
			auto& types = plugin->GetForms();
			auto doForms = [&](RE::FormType a_type) {
				if (types.contains(a_type)) {
					Item::ItemForm form{ a_type, types[a_type].size() };
					_formList.push_back(form);
				}
			};

			doForms(RE::FormType::AlchemyItem);
			doForms(RE::FormType::Ammo);
			doForms(RE::FormType::Armor);
			doForms(RE::FormType::Book);
			doForms(RE::FormType::Ingredient);
			doForms(RE::FormType::KeyMaster);
			doForms(RE::FormType::Misc);
			doForms(RE::FormType::Note);
			doForms(RE::FormType::Scroll);
			doForms(RE::FormType::SoulGem);
			doForms(RE::FormType::Spell);
			doForms(RE::FormType::Weapon);
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
			_pluginListIndex = _pluginList.SelectedIndex();
		} else if (_focus == Focus::Form) {
			_formList.ModSelectedIndex(a_mod);
			_formListIndex = _formList.SelectedIndex();
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
				_focus = Focus::Container;
				_formName = form->GetName();
				_formType = form->GetType();
				Close();
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
			_formType = RE::FormType::None;
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
		std::string str = "";
		if (_focus == Focus::Form) {
			str = _pluginName;
		} else {
			auto locale = LocaleManager::GetSingleton();
			auto locStr = LocaleStrings::GetSingleton();
			str = locale->Translate(locStr->plugPlugins);
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
			indexAccept = General::Input::GetGamepadIndex(Key::kA);
			indexCancel = General::Input::GetGamepadIndex(Key::kBack);
		} else {
			using Key = RE::BSWin32KeyboardDevice::Key;
			indexAccept = General::Input::GetKeyboardIndex(Key::kEnter);
			indexCancel = General::Input::GetKeyboardIndex(Key::kEscape);
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
