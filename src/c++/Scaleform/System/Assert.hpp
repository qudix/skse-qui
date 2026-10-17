#pragma once

namespace SF
{
#ifndef NDEBUG
	template <class T, class... A>
	inline T Assert(T&& a_expression, [[maybe_unused]] std::format_string<A...> a_msg = "", [[maybe_unused]] std::source_location a_loc = std::source_location::current())
	{
		if (!a_expression)
			REX::FAIL(a_msg, a_loc);

		return std::move(a_expression);
	}
#else
	template <class T>
	inline T Assert(T&& a_expression, [[maybe_unused]] std::string_view a_msg = "")
	{
		return std::move(a_expression);
	}
#endif
}
