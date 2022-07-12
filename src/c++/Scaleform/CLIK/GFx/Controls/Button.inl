#pragma once

namespace SF::CLIK::GFx::Controls
{
	inline Button::Button(const super& a_rhs) :
		super(a_rhs)
	{}

	inline Button::Button(super&& a_rhs) :
		super(std::move(a_rhs))
	{}

	inline Button& Button::operator=(const super& a_rhs)
	{
		super::operator=(a_rhs);
		return *this;
	}

	inline Button& Button::operator=(super&& a_rhs)
	{
		super::operator=(std::move(a_rhs));
		return *this;
	}
}

namespace SF::CLIK::GFx::Controls
{
	inline void Button::SetSize(double a_width, double a_height)
	{
		Assert(InvokeA("setSize", nullptr, a_width, a_height));
	}

	inline std::string Button::ToString()
	{
		RE::GFxValue str;
		Assert(Invoke("toString", std::addressof(str)));
		return str.GetString();
	}
}
