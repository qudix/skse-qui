#pragma once

#include "Core/Locale/LocaleManager.hpp"
#include "Core/Locale/LocaleStrings.hpp"

namespace Core::Menu::Item
{
	struct ItemForm
	{
		ItemForm(RE::FormType a_type, size_t a_count) :
			_type(a_type),
			_count(a_count)
		{
			auto locale = LocaleManager::GetSingleton();
			auto locStr = LocaleStrings::GetSingleton();
			const auto& type = locStr->FormType(a_type);
			_name = locale->Translate(type);
		}

		[[nodiscard]] RE::GFxValue GFxValue(RE::GFxMovieView& a_view) const
		{
			RE::GFxValue value;
			a_view.CreateObject(std::addressof(value));

			value.SetMember("name", { GetName() });
			value.SetMember("count", { GetCount() });

			return value;
		}

		[[nodiscard]] const RE::FormType GetType() const noexcept { return _type; }
		[[nodiscard]] std::string_view GetName() const noexcept { return _name; }
		[[nodiscard]] const size_t GetCount() const noexcept { return _count; }

	private:
		RE::FormType _type;
		std::string	 _name{ "" };
		size_t		 _count{ 0 };
	};
}
