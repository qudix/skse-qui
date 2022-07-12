#pragma once

namespace SF::CLIK::GFx::Controls
{
	inline ButtonBar::ButtonBar(const super& a_rhs) :
		super(a_rhs)
	{}

	inline ButtonBar::ButtonBar(super&& a_rhs) :
		super(std::move(a_rhs))
	{}

	inline ButtonBar& ButtonBar::operator=(const super& a_rhs)
	{
		super::operator=(a_rhs);
		return *this;
	}

	inline ButtonBar& ButtonBar::operator=(super&& a_rhs)
	{
		super::operator=(std::move(a_rhs));
		return *this;
	}
}

namespace SF::CLIK::GFx::Controls
{
	inline void ButtonBar::InvalidateData()
	{
		Assert(Invoke("invalidateData"));
	}

	inline std::string ButtonBar::ItemToLabel(Object a_item)
	{
		RE::GFxValue str;
		Assert(InvokeA("itemToLabel", std::addressof(str), a_item));
		return str.GetString();
	}

	inline std::string ButtonBar::ToString()
	{
		RE::GFxValue str;
		Assert(Invoke("toString", std::addressof(str)));
		return str.GetString();
	}
}
