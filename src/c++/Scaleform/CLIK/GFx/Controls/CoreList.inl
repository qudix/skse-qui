#pragma once

namespace SF::CLIK::GFx::Controls
{
	inline CoreList::CoreList(const super& a_rhs) :
		super(a_rhs)
	{}

	inline CoreList::CoreList(super&& a_rhs) :
		super(std::move(a_rhs))
	{}

	inline CoreList& CoreList::operator=(const super& a_rhs)
	{
		super::operator=(a_rhs);
		return *this;
	}

	inline CoreList& CoreList::operator=(super&& a_rhs)
	{
		super::operator=(std::move(a_rhs));
		return *this;
	}
}

namespace SF::CLIK::GFx::Controls
{
	inline void CoreList::ScrollToIndex(double a_index)
	{
		Assert(InvokeA("scrollToIndex", nullptr, a_index));
	}

	inline std::string CoreList::ItemToLabel(Object& a_item)
	{
		RE::GFxValue str;
		Assert(InvokeA("itemToLabel", std::addressof(str), a_item));
		return str.GetString();
	}

	inline void CoreList::InvalidateData()
	{
		Assert(Invoke("invalidateData"));
	}

	inline void CoreList::SetRendererList(Array& a_value)
	{
		Assert(InvokeA("setRendererList", nullptr, a_value));
	}

	inline std::string CoreList::ToString()
	{
		RE::GFxValue str;
		Assert(Invoke("toString", std::addressof(str)));
		return str.GetString();
	}
}
