#pragma once

namespace SF::CLIK::GFx::Core
{
	inline UIComponent::UIComponent(const super& a_rhs) :
		super(a_rhs)
	{}

	inline UIComponent::UIComponent(super&& a_rhs) :
		super(std::move(a_rhs))
	{}

	inline UIComponent& UIComponent::operator=(const super& a_rhs)
	{
		super::operator=(a_rhs);
		return *this;
	}

	inline UIComponent& UIComponent::operator=(super&& a_rhs)
	{
		super::operator=(std::move(a_rhs));
		return *this;
	}
}

namespace SF::CLIK::GFx::Core
{
	inline void UIComponent::SetSize(double a_width, double a_height)
	{
		Assert(InvokeA("setSize", nullptr, a_width, a_height));
	}

	inline void UIComponent::Invalidate()
	{
		Assert(Invoke("invalidate"));
	}

	inline void UIComponent::ValidateNow()
	{
		Assert(Invoke("validateNow"));
	}

	inline std::string UIComponent::ToString()
	{
		RE::GFxValue str;
		Assert(Invoke("toString", std::addressof(str)));
		return str.GetString();
	}

	inline void UIComponent::DispatchEventToGame(Object& a_event)
	{
		Assert(InvokeA("dispatchEventToGame", nullptr, a_event));
	}
}
