#include "Core/Menu/StartMenu.hpp"

#include "Scaleform/System/Function.hpp"
#include "Scaleform/System/Logger.hpp"

#include "Core/Config.hpp"

namespace Core::Menu
{
    class StartGetSetting : public RE::GFxFunctionHandler
    {
    public:
        void Call(Params& a_args) override
        {
            bool result = true;
            std::string id = a_args.args[0].GetString();
            auto& config = Config::Get();
            if (id == "CC") {
                result = config.MainMenu.List.CC;
            } else if (id == "DLC") {
                result = config.MainMenu.List.DLC;
            } else if (id == "Mods") {
                result = config.MainMenu.List.Mods;
            } else if (id == "Credits") {
                result = config.MainMenu.List.Credits;
            } else if (id == "Help") {
                result = config.MainMenu.List.Help;
            } else if (id == "Logo") {
                result = config.MainMenu.UI.Logo;
            } else if (id == "Motd") {
                result = config.MainMenu.UI.Motd;
            }

            a_args.retVal->SetBoolean(result);
        }
    };

    void StartMenu::Register(RE::GFxMovieView* a_view, RE::GFxValue* a_root)
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
