#pragma once

#include "Scaleform/CLIK/Object.h"

namespace CLIK
{
	class Array :
		public Object
	{
	private:
		using super = Object;

	public:
		Array() = default;
		Array(const Array&) = default;
		Array(Array&&) = default;
		using super::super;

		Array(const super& a_rhs) :
			super(a_rhs)
		{}

		Array(super&& a_rhs) :
			super(std::move(a_rhs))
		{}

		Array(const RE::GFxValue& a_rhs) :
			super(a_rhs)
		{
			assert(IsArray());
		}

		Array(RE::GFxValue&& a_rhs) :
			super(std::move(a_rhs))
		{
			assert(IsArray());
		}

		Array(RE::GPtr<RE::GFxMovieView> a_rhs) :
			super()
		{
			CreateArray(std::move(a_rhs));
		}

		~Array() = default;

		Array& operator=(const Array&) = default;
		Array& operator=(Array&&) = default;
		using super::operator=;

		Array& operator=(const super& a_rhs)
		{
			super::operator=(a_rhs);
			return *this;
		}

		Array& operator=(super&& a_rhs)
		{
			super::operator=(std::move(a_rhs));
			return *this;
		}

		Array& operator=(const RE::GFxValue& a_rhs)
		{
			super::operator=(a_rhs);
			assert(IsArray());
			return *this;
		}

		Array& operator=(RE::GFxValue&& a_rhs)
		{
			super::operator=(std::move(a_rhs));
			assert(IsArray());
			return *this;
		}

		Array& operator=(RE::GPtr<RE::GFxMovieView> a_rhs)
		{
			CreateArray(std::move(a_rhs));
			return *this;
		}

		// properties
		static constexpr double CASEINSENSITIVE = 1;
		static constexpr double DESCENDING = 2;
		static constexpr double NUMERIC = 16;
		static constexpr double RETURNINDEXEDARRAY = 8;
		static constexpr double UNIQUESORT = 4;

		double Length() const { return GetNumber("length"); }
		void Length(double a_length) { SetNumber("length", a_length); }

		// methods
		Array Concat(std::optional<std::reference_wrapper<Object>> a_value)
		{
			RE::GFxValue arr;

			if (a_value) {
				enum
				{
					kValue,
					kNumArgs
				};

				std::array<RE::GFxValue, kNumArgs> args;

				args[kValue] = a_value->get().GetInstance();
				assert(args[kValue].IsObject());

				[[maybe_unused]] const auto success =
					Invoke("concat", std::addressof(arr), args.data(), args.size());
				assert(success);
			} else {
				[[maybe_unused]] const auto success =
					Invoke("concat", std::addressof(arr), nullptr, 0);
				assert(success);
			}

			return Array(arr);
		}

		std::string Join(std::optional<std::string_view> a_delimiter)
		{
			enum
			{
				kDelimiter,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;
			std::size_t size = 0;

			if (a_delimiter) {
				args[kDelimiter] = *a_delimiter;
				assert(args[kDelimiter].IsString());
				++size;
			}

			auto data = size > 0 ? args.data() : nullptr;
			RE::GFxValue str;
			[[maybe_unused]] const auto success =
				Invoke("join", std::addressof(str), data, size);
			assert(success);

			return str.GetString();
		}

		Object Pop()
		{
			RE::GFxValue object;
			[[maybe_unused]] const auto success =
				Invoke("pop", std::addressof(object));
			assert(success);
			return Object(object);
		}

		double Push(Object& a_value)
		{
			enum
			{
				kValue,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kValue] = a_value.GetInstance();

			RE::GFxValue number;
			[[maybe_unused]] const auto success =
				Invoke("push", std::addressof(number), args.data(), args.size());
			assert(success);

			return number.GetNumber();
		}

		void Reverse()
		{
			[[maybe_unused]] const auto success =
				Invoke("reverse");
			assert(success);
		}

		Object Shift()
		{
			RE::GFxValue object;
			[[maybe_unused]] const auto success =
				Invoke("shift", std::addressof(object));
			assert(success);
			return Object(object);
		}

		void Splice(double a_startIndex, std::optional<double> a_deleteCount, std::optional<Object> a_value)
		{
			enum
			{
				kStartIndex,
				kDeleteCount,
				kValue,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;
			std::size_t size = 1;

			args[kStartIndex] = a_startIndex;
			assert(args[kStartIndex].IsNumber());

			if (a_deleteCount) {
				args[kDeleteCount] = *a_deleteCount;
				assert(args[kDeleteCount].IsNumber());
				++size;

				if (a_value) {
					args[kValue] = a_value->GetInstance();
					++size;
				}
			}

			[[maybe_unused]] const auto success =
				Invoke("push", nullptr, args.data(), size);
			assert(success);
		}
	};
}
