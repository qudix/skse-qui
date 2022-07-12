#pragma once

#include "Scaleform/Object.hpp"

namespace SF
{
	class Array :
		public Object
	{
	private:
		using super = Object;

	public:
		using super::super;
		using super::operator=;

		Array() = default;
		Array(const Array&) = default;
		Array(Array&&) = default;
		Array(const super& a_rhs);
		Array(super&& a_rhs);
		Array(const RE::GFxValue& a_rhs);
		Array(RE::GFxValue&& a_rhs);
		Array(RE::GPtr<RE::GFxMovieView> a_rhs);

		~Array() = default;

		Array& operator=(const Array&) = default;
		Array& operator=(Array&&) = default;
		Array& operator=(const super& a_rhs);
		Array& operator=(super&& a_rhs);
		Array& operator=(const RE::GFxValue& a_rhs);
		Array& operator=(RE::GFxValue&& a_rhs);
		Array& operator=(RE::GPtr<RE::GFxMovieView> a_rhs);

	public:
		// Constants
		static constexpr auto CASE_INSENSITIVE{ 1.0 };
		static constexpr auto DESCENDING{ 2.0 };
		static constexpr auto NUMERIC{ 16.0 };
		static constexpr auto RETURN_INDEXED_ARRAY{ 8.0 };
		static constexpr auto UNIQUE_SORT{ 4.0 };

		// Properties
		double Length() const { return GetNumber("length"); }
		void   Length(double a_length) { SetNumber("length", a_length); }

	public:
		// Methods
		Array       Concat(std::optional<std::reference_wrapper<Object>> a_value);
		std::string Join(std::optional<std::string_view> a_delimiter);
		Object      Pop();
		double      Push(Object& a_value);
		void        Reverse();
		Object      Shift();
		void        Splice(double a_startIndex, std::optional<double> a_deleteCount, std::optional<Object> a_value);
	};
}

#include "Array.inl"
