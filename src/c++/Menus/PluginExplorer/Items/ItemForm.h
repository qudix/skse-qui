#pragma once

namespace Menus::Item
{
	struct ItemForm
	{
		ItemForm(RE::FormType a_type, size_t a_count) :
			_type(a_type),
			_count(a_count)
		{
			switch (a_type) {
			case RE::FormType::Ammo:
				_name = "Ammo";
				break;
			case RE::FormType::Armor:
				_name = "Armor";
				break;
			case RE::FormType::AlchemyItem:
				_name = "Alchemy";
				break;
			case RE::FormType::Book:
				_name = "Book";
				break;
			case RE::FormType::Ingredient:
				_name = "Ingredient";
				break;
			case RE::FormType::KeyMaster:
				_name = "Key";
				break;
			case RE::FormType::Misc:
				_name = "Misc";
				break;
			case RE::FormType::Note:
				_name = "Note";
				break;
			case RE::FormType::Spell:
				_name = "Spell";
				break;
			case RE::FormType::Weapon:
				_name = "Weapon";
				break;
			default:
				_name = "Unhandled";
			}
		}

		[[nodiscard]]
		RE::GFxValue GFxValue(RE::GFxMovieView& a_view) const
		{
			RE::GFxValue value;
			a_view.CreateObject(std::addressof(value));

			value.SetMember("name", { _name });
			value.SetMember("count", { _count });
			return value;
		}

		[[nodiscard]] RE::FormType GetType() { return _type; }
		[[nodiscard]] std::string_view& GetName() { return _name; }

		RE::FormType _type;
		std::string_view _name{ "" };
		size_t _count{ 0 };
	};
}
