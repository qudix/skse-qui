#pragma once

#include "General/Singleton.hpp"

namespace Core::Private
{
    struct ConfigImpl
    {
        struct
        {
            bool Pause;
            bool Loop;
            bool Sound;

            struct
            {
                uint32_t KeyboardToggle;
            } Key;

            struct
            {
                uint32_t Alchemy;
                uint32_t Ammo;
                uint32_t Armor;
                uint32_t Book;
                uint32_t Ingredient;
                uint32_t Key;
                uint32_t Misc;
                uint32_t Note;
                uint32_t Soul;
                uint32_t Spell;
                uint32_t Weapon;
            } Count;
        } PluginExplorer;

        struct
        {
            struct
            {
                bool Logo;
                bool Motd;
            } UI;

            struct
            {
                bool CC;
                bool DLC;
                bool Mods;
                bool Credits;
                bool Help;
            } List;
        } MainMenu;
    };
}

namespace Core
{
    class Config final :
        public General::Singleton<Config>
    {
    public:
        Config() = default;

        void Load();
        void Read();

        toml::node_view<toml::node> GetNode(const char* a_path);

        bool GetValue(const char* a_path, bool a_default);
        uint32_t GetValue(const char* a_path, uint32_t a_default);

        static Private::ConfigImpl& Get();

    public:
        toml::parse_result _result;
        toml::parse_result _resultCustom;

        Private::ConfigImpl _impl{};
    };
}
