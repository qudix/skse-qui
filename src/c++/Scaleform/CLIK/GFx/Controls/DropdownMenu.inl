#pragma once

namespace SF::CLIK::GFx::Controls
{
	inline DropdownMenu::DropdownMenu(const super& a_rhs) :
		super(a_rhs)
	{}

	inline DropdownMenu::DropdownMenu(super&& a_rhs) :
		super(std::move(a_rhs))
	{}

	inline DropdownMenu& DropdownMenu::operator=(const super& a_rhs)
	{
		super::operator=(a_rhs);
		return *this;
	}

	inline DropdownMenu& DropdownMenu::operator=(super&& a_rhs)
	{
		super::operator=(std::move(a_rhs));
		return *this;
	}
}

namespace SF::CLIK::GFx::Controls
{
	inline void DropdownMenu::Close()
	{
		Assert(Invoke("close"));
	}

	inline void DropdownMenu::InvalidateData()
	{
		Assert(Invoke("invalidateData"));
	}

	inline std::string DropdownMenu::ItemToLabel(Object& a_item)
	{
		RE::GFxValue str;
		Assert(InvokeA("itemToLabel", std::addressof(str), a_item));
		return str.GetString();
	}

	inline void DropdownMenu::Open()
	{
		Assert(Invoke("open"));
	}

	inline void DropdownMenu::RemoveMovieClip()
	{
		Assert(Invoke("removeMovieClip"));
	}

	inline void DropdownMenu::SetSize(double a_width, double a_height)
	{
		Assert(InvokeA("setSize", nullptr, a_width, a_height));
	}

	inline std::string DropdownMenu::ToString()
	{
		RE::GFxValue str;
		Assert(Invoke("toString", std::addressof(str)));
		return str.GetString();
	}
}
