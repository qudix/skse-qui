#pragma once

namespace SF::CLIK::GFx::Controls
{
	inline TextInput::TextInput(const super& a_rhs) :
		super(a_rhs)
	{}

	inline TextInput::TextInput(super&& a_rhs) :
		super(std::move(a_rhs))
	{}

	inline TextInput& TextInput::operator=(const super& a_rhs)
	{
		super::operator=(a_rhs);
		return *this;
	}

	inline TextInput& TextInput::operator=(super&& a_rhs)
	{
		super::operator=(std::move(a_rhs));
		return *this;
	}
}

namespace SF::CLIK::GFx::Controls
{
	inline void TextInput::AppendHTML(std::string_view a_text)
	{
		Assert(InvokeA("appendHtml", nullptr, a_text));
	}

	inline void TextInput::AppendText(std::string_view a_text)
	{
		Assert(InvokeA("appendText", nullptr, a_text));
	}

	inline std::string TextInput::ToString()
	{
		RE::GFxValue str;
		Assert(Invoke("toString", std::addressof(str)));
		return str.GetString();
	}
}
