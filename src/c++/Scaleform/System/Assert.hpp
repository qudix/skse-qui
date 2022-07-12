#pragma once

namespace SF
{
#ifndef NDEBUG
	template <typename T>
	inline T Assert(T&& a_expression, [[maybe_unused]] std::string_view a_msg = "", [[maybe_unused]] std::source_location a_loc = std::source_location::current())
	{
		if (!a_expression)
			stl::report_and_fail(a_msg, a_loc);

		return std::move(a_expression);
	}
#else
	template <typename T>
	inline T Assert(T&& a_expression, [[maybe_unused]] std::string_view a_msg = "")
	{
		return std::move(a_expression);
	}
#endif
}
