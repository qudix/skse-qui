#pragma once

namespace Core::Locale
{
	inline std::optional<std::wstring> SanitizeKey(std::wstring a_key)
	{
		using size_type = std::wstring::size_type;
		std::stack<size_type> stack;
		for (size_type pos = 0; pos < a_key.size(); ++pos) {
			switch (a_key[pos]) {
				case L'{':
					stack.push(pos);
					break;
				case L'}':
					{
						switch (stack.size()) {
							case 0:
								return std::nullopt;
							case 1:
								{
									size_type last = stack.top();
									stack.pop();
									auto off = last + 1;
									auto count = pos - last - 1;
									if (count > 0) {
										a_key.replace(off, count, L"");
									}
									pos = off;
								}
								break;
							default:
								stack.pop();
						}
						break;
					}
			}
		}

		if (!a_key.empty() && a_key.back() == L'\r')
			a_key.pop_back();

		return std::make_optional(a_key);
	}
}
