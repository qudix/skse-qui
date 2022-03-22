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

		[[nodiscard]] RE::GFxValue GFxValue(RE::GFxMovieView& a_view) const
		{
			std::string index;
			if (_index >= 0xFE) {
				index = fmt::format(FMT_STRING("FE {:03X}"), _index - 0xFE);
			} else {
				index = fmt::format(FMT_STRING("{:02X}"), _index);
			}

			RE::GFxValue value;
			a_view.CreateObject(std::addressof(value));

			value.SetMember("index", { static_cast<std::string_view>(index) });
			value.SetMember("name", { GetName() });
			value.SetMember("count", { GetCount() });

			return value;
		}

		[[nodiscard]] const uint32_t GetIndex() const noexcept { return _index; }
		[[nodiscard]] std::string_view GetName() const noexcept { return _name; }
		[[nodiscard]] const size_t GetCount() const noexcept { return _count; }

	private:
		uint32_t	_index;
		std::string _name{ "" };
		size_t		_count{ 0 };
	};
}
