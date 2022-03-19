#pragma once

namespace Core::Menu
{
	class MainMenuEx : public RE::MainMenu
	{
	public:
		static void Install();
		static void ProcessEx(RE::GPtr<RE::GFxMovieView> a_movie);

	public:
		RE::UI_MESSAGE_RESULTS ProcessMessageEx(RE::UIMessage& a_message);  // 04

	private:
		using ProcessMessageFn = decltype(&RE::MainMenu::ProcessMessage);

		inline static REL::Relocation<ProcessMessageFn> _ProcessMessageFn;

		inline static bool _show{ false };
	};
}
