#pragma once

namespace SF::CLIK::GFx::Controls
{
	inline ScrollingList::ScrollingList(const super& a_rhs) :
		super(a_rhs)
	{}

	inline ScrollingList::ScrollingList(super&& a_rhs) :
		super(std::move(a_rhs))
	{}

	inline ScrollingList& ScrollingList::operator=(const super& a_rhs)
	{
		super::operator=(a_rhs);
		return *this;
	}

	inline ScrollingList& ScrollingList::operator=(super&& a_rhs)
	{
		super::operator=(std::move(a_rhs));
		return *this;
	}
}

namespace SF::CLIK::GFx::Controls
{
	inline void ScrollingList::InvalidateData()
	{
		Assert(Invoke("invalidateData"));
	}

	inline void ScrollingList::ScrollToIndex(double a_index)
	{
		Assert(InvokeA("scrollToIndex", nullptr, a_index));
	}

	inline std::string ScrollingList::ToString()
	{
		RE::GFxValue str;
		Assert(Invoke("toString", std::addressof(str)));
		return str.GetString();
	}
}
