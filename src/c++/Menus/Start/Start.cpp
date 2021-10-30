#include "Menus/Start/Start.h"

#include "Scaleform/System/Function.h"
#include "Scaleform/System/Logger.h"

namespace Menus
{
	class StartGetSetting : public RE::GFxFunctionHandler
	{
	public:
		void Call(Params& a_args) override
		{
			std::string id = a_args.args[0].GetString();
			bool result = true;
			if (id == "CC") {
				result = Settings::MainMenu.List.CC;
			} else if (id == "DLC") {
				result = Settings::MainMenu.List.DLC;
			} else if (id == "Mods") {
				result = Settings::MainMenu.List.Mods;
			} else if (id == "Credits") {
				result = Settings::MainMenu.List.Credits;
			} else if (id == "Help") {
				result = Settings::MainMenu.List.Help;
			} else if (id == "Logo") {
				result = Settings::MainMenu.UI.Logo;
			} else if (id == "Motd") {
				result = Settings::MainMenu.UI.Motd;
			}

			a_args.retVal->SetBoolean(result);
		}
	};

	void Start::Register(RE::GFxMovieView* a_view, RE::GFxValue* a_root)
	{
		auto def = a_view->GetMovieDef();
		std::string url = def->GetFileURL();
		if (url != "Interface/StartMenu.swf")
			return;

		def->SetState(
			RE::GFxState::StateType::kLog,
			RE::make_gptr<Scaleform::Logger<RE::MainMenu>>().get());

		RE::GFxValue result;
		RE::GFxValue args[2];
		RE::GFxValue component;

		args[0].SetString("StartMenuExContainer");
		a_view->Invoke("_root.getNextHighestDepth", &args[1], nullptr, 0);
		a_view->Invoke("_root.createEmptyMovieClip", &component, args, 2);

		RE::GFxValue swf{ "StartMenuEx.swf" };
		bool success = component.Invoke("loadMovie", &result, &swf, 1);
		if (!success)
			logger::info("Injection failed");

		// TODO: Scaleform::RegisterFunction doesn't work, so I'm doing this manually
		// Scaleform::RegisterFunction<StartGetSetting>(a_view, a_root, "StartGetSetting");
		RE::GFxFunctionHandler* fn = new StartGetSetting;
		RE::GFxValue dst;
		a_view->CreateFunction(&dst, fn);
		a_root->SetMember("StartGetSetting", dst);
	}
}
