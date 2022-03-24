#include "Core/Menu/JournalMenu.hpp"

#include "Core/Config.hpp"

namespace Core::Menu
{
	void JournalMenuEx::AcceptEx(RE::FxDelegateHandler::CallbackProcessor* a_cbReg)
	{
		_AcceptFn(this, a_cbReg);
		fxDelegate->callbacks.Remove("RememberCurrentTabIndex");
		a_cbReg->Process("RememberCurrentTabIndex", [](const RE::FxDelegateArgs&) {
			// Empty
		});
	}

	RE::UI_MESSAGE_RESULTS JournalMenuEx::ProcessMessageEx(RE::UIMessage& a_message)
	{
		using Message = RE::UI_MESSAGE_TYPE;
		if (a_message.type == Message::kShow) {
			auto ui = RE::UI::GetSingleton();
			auto uiStr = RE::InterfaceStrings::GetSingleton();
			if (ui->IsMenuOpen(uiStr->mapMenu)) {
				*_savedTabIdx = Tab::kQuest;
			} else {
				auto& config = Config::Get();
				*_savedTabIdx = static_cast<Tab>(config.JournalMenu.DefaultPage);
			}
		}

		return _ProcessMessageFn(this, a_message);
	}

	void JournalMenuEx::Install()
	{
		REL::Relocation<uintptr_t> vtbl(RE::VTABLE_JournalMenu[0]);
		_AcceptFn = vtbl.write_vfunc(0x1, &AcceptEx);
		_ProcessMessageFn = vtbl.write_vfunc(0x4, &ProcessMessageEx);
	}
}
