#pragma once

#include "Core/LocaleManager.hpp"

namespace Core::Menu::Item
{
    struct ItemForm
    {
        ItemForm(RE::FormType a_type, size_t a_count) :
            _type(a_type),
            _count(a_count)
        {
            std::string key = "";
            switch (a_type) {
            case RE::FormType::AlchemyItem:
                key = "$QDX_QUI_FORM_ALCH";
                break;
            case RE::FormType::Ammo:
                key = "$QDX_QUI_FORM_AMMO";
                break;
            case RE::FormType::Armor:
                key = "$QDX_QUI_FORM_ARMO";
                break;
            case RE::FormType::Book:
                key = "$QDX_QUI_FORM_BOOK";
                break;
            case RE::FormType::Ingredient:
                key = "$QDX_QUI_FORM_INGR";
                break;
            case RE::FormType::KeyMaster:
                key = "$QDX_QUI_FORM_KEYM";
                break;
            case RE::FormType::Misc:
                key = "$QDX_QUI_FORM_MISC";
                break;
            case RE::FormType::Note:
                key = "$QDX_QUI_FORM_NOTE";
                break;
            case RE::FormType::Spell:
                key = "$QDX_QUI_FORM_SPEL";
                break;
            case RE::FormType::Weapon:
                key = "$QDX_QUI_FORM_WEAP";
                break;
            }

            auto locale = LocaleManager::GetSingleton();
            _name = !key.empty() ? locale->Translate(key) : "[Unhandled]";
        }

        [[nodiscard]]
        RE::GFxValue GFxValue(RE::GFxMovieView& a_view) const
        {
            RE::GFxValue value;
            a_view.CreateObject(std::addressof(value));

            value.SetMember("name", { static_cast<std::string_view>(GetName()) });
            value.SetMember("count", { _count });
            return value;
        }

        [[nodiscard]] const RE::FormType GetType() const noexcept { return _type; }
        [[nodiscard]] const std::string& GetName() const noexcept { return _name; }

        RE::FormType _type;
        std::string _name{ "" };
        size_t _count{ 0 };
    };
}
