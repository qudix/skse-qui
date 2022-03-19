#pragma once

namespace Core::Menu
{
	class JournalMenuEx : public RE::JournalMenu
	{
	public:
		enum class Tab : uint32_t
		{
			kQuest,
			kPlayerInfo,
			kSystem
		};

		static void Install();

	public:
		void				   AcceptEx(RE::FxDelegateHandler::CallbackProcessor* a_cbReg);  // 01
		RE::UI_MESSAGE_RESULTS ProcessMessageEx(RE::UIMessage& a_message);					 // 04

	private:
		using AcceptFn = decltype(&RE::JournalMenu::Accept);
		using ProcessMessageFn = decltype(&RE::JournalMenu::ProcessMessage);

		inline static REL::Relocation<AcceptFn>			_AcceptFn;
		inline static REL::Relocation<ProcessMessageFn> _ProcessMessageFn;
		inline static REL::Relocation<Tab*>				_savedTabIdx{ RELOCATION_ID(520167, 406697) };
	};
}
