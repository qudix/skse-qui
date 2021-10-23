#pragma once

namespace Menus::Item
{
	struct ItemPlugin
	{
		ItemPlugin(uint32_t a_formID, std::string_view a_name, size_t a_count) :
			_formID(a_formID),
			_name(a_name),
			_count(a_count)
		{}

		[[nodiscard]]
		RE::GFxValue GFxValue(RE::GFxMovieView& a_view) const
		{
			RE::GFxValue value;
			a_view.CreateObject(std::addressof(value));

			std::string index;
			if (_formID >= 0xFE) {
				index = fmt::format(FMT_STRING("FE {:03X}"), _formID - 0xFE);
			} else {
				index = fmt::format(FMT_STRING("{:02X}"), _formID);
			}

			value.SetMember("index", { static_cast<std::string_view>(index) });
			value.SetMember("name", { _name });
			value.SetMember("count", { _count });
			return value;
		}

		[[nodiscard]]
		std::string_view GetName()
		{
			return _name;
		}

		[[nodiscard]]
		uint32_t GetFormID() {
			return _formID;
		}

		uint32_t _formID;
		std::string_view _name;
		size_t _count;
	};
}
