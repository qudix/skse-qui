#pragma once

namespace SF::CLIK::GFx::Controls
{
	inline Slider::Slider(const super& a_rhs) :
		super(a_rhs)
	{}

	inline Slider::Slider(super&& a_rhs) :
		super(std::move(a_rhs))
	{}

	inline Slider& Slider::operator=(const super& a_rhs)
	{
		super::operator=(a_rhs);
		return *this;
	}

	inline Slider& Slider::operator=(super&& a_rhs)
	{
		super::operator=(std::move(a_rhs));
		return *this;
	}
}

namespace SF::CLIK::GFx::Controls
{
	inline std::string Slider::ToString()
	{
		RE::GFxValue str;
		Assert(Invoke("toString", std::addressof(str)));
		return str.GetString();
	}
}
