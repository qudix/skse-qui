#pragma once

namespace SF
{
	class Logger : public RE::GFxLog
	{
	public:
		Logger() = default;
		Logger(std::string_view a_name) :
			_name(a_name)
		{}

		void LogMessageVarg(LogMessageType, const char* a_fmt, std::va_list a_argList) override
		{
			std::string fmt(a_fmt ? a_fmt : "");
			while (!fmt.empty() && fmt.back() == '\n') {
				fmt.pop_back();
			}

			std::va_list args;
			va_copy(args, a_argList);
			std::vector<char> buf(static_cast<size_t>(std::vsnprintf(0, 0, fmt.c_str(), a_argList) + 1));
			std::vsnprintf(buf.data(), buf.size(), fmt.c_str(), args);
			va_end(args);

			if (_name.empty())
				logger::info("{}"sv, buf.data());
			else
				logger::info("{}: {}"sv, _name, buf.data());
		}

	private:
		std::string _name{ "" };
	};

	inline Logger* make_logger(std::string_view a_name)
	{
		return RE::make_gptr<Logger>(a_name).get();
	}
}
