#pragma once

namespace SF
{
	inline Array::Array(const super& a_rhs) :
		super(a_rhs)
	{}

	inline Array::Array(super&& a_rhs) :
		super(std::move(a_rhs))
	{}

	inline Array::Array(const RE::GFxValue& a_rhs) :
		super(a_rhs)
	{
		Assert(IsArray());
	}

	inline Array::Array(RE::GFxValue&& a_rhs) :
		super(std::move(a_rhs))
	{
		Assert(IsArray());
	}

	inline Array::Array(RE::GPtr<RE::GFxMovieView> a_rhs) :
		super()
	{
		CreateArray(std::move(a_rhs));
	}

	inline Array& Array::operator=(const super& a_rhs)
	{
		super::operator=(a_rhs);
		return *this;
	}

	inline Array& Array::operator=(super&& a_rhs)
	{
		super::operator=(std::move(a_rhs));
		return *this;
	}

	inline Array& Array::operator=(const RE::GFxValue& a_rhs)
	{
		super::operator=(a_rhs);
		Assert(IsArray());
		return *this;
	}

	inline Array& Array::operator=(RE::GFxValue&& a_rhs)
	{
		super::operator=(std::move(a_rhs));
		Assert(IsArray());
		return *this;
	}

	inline Array& Array::operator=(RE::GPtr<RE::GFxMovieView> a_rhs)
	{
		CreateArray(std::move(a_rhs));
		return *this;
	}
}

namespace SF
{
	inline Array Array::Concat(std::optional<std::reference_wrapper<Object>> a_value)
	{
		RE::GFxValue arr;
		if (a_value)
			Assert(InvokeA("concat", std::addressof(arr), a_value->get()));
		else
			Assert(Invoke("concat", std::addressof(arr), nullptr, 0));

		return Array(arr);
	}

	inline std::string Array::Join(std::optional<std::string_view> a_delimiter)
	{
		RE::GFxValue str;
		if (a_delimiter)
			Assert(InvokeA("join", std::addressof(str), *a_delimiter));
		else
			Assert(Invoke("join", std::addressof(str), nullptr, 0));

		return str.GetString();
	}

	inline Object Array::Pop()
	{
		RE::GFxValue object;
		Assert(Invoke("pop", std::addressof(object)));
		return Object(object);
	}

	inline double Array::Push(Object& a_value)
	{
		RE::GFxValue number;
		Assert(InvokeA("push", std::addressof(number), a_value));
		return number.GetNumber();
	}

	inline void Array::Reverse()
	{
		Assert(Invoke("reverse"));
	}

	inline Object Array::Shift()
	{
		RE::GFxValue object;
		Assert(Invoke("shift", std::addressof(object)));
		return Object(object);
	}

	inline void Array::Splice(double a_startIndex, std::optional<double> a_deleteCount, std::optional<Object> a_value)
	{
		if (a_deleteCount) {
			if (a_value)
				Assert(InvokeA("push", nullptr, a_startIndex, *a_deleteCount, *a_value));
			else
				Assert(InvokeA("push", nullptr, a_startIndex, *a_deleteCount));
		} else {
			Assert(InvokeA("push", nullptr, a_startIndex));
		}
	}
}
