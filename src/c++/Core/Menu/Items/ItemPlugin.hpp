#pragma once

namespace Core::Menu::Item
{
	struct ItemPlugin
	{
		ItemPlugin(uint32_t a_index, std::string_view a_name, size_t a_count) :
			_index(a_index),
			_name(a_name),
			_count(a_count)
		{}

		[[nodiscard]]
		RE::GFxValue GFxValue(RE::GFxMovieView& a_view) const
		{
			RE::GFxValue value;
			a_view.CreateObject(std::addressof(value));

			std::string index;
			if (_index >= 0xFE) {
				index = fmt::format(FMT_STRING("FE {:03X}"), _index - 0xFE);
			} else {
				index = fmt::format(FMT_STRING("{:02X}"), _index);
			}

			value.SetMember("index", { static_cast<std::string_view>(index) });
			value.SetMember("name", { _name });
			value.SetMember("count", { _count });
			return value;
		}

		[[nodiscard]] std::string_view GetName() { return _name; }
		[[nodiscard]] uint32_t GetIndex() { return _index; }

		uint32_t _index;
		std::string_view _name;
		size_t _count;
	};
}
