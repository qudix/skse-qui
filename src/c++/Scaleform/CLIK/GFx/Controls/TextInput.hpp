#pragma once

#include "Scaleform/CLIK/GFx/Core/UIComponent.hpp"

namespace SF::CLIK::GFx::Controls
{
	class TextInput :
		public Core::UIComponent
	{
		using super = Core::UIComponent;

	public:
		using super::super;
		using super::operator=;

		TextInput() = default;
		TextInput(const TextInput&) = default;
		TextInput(TextInput&&) = default;
		TextInput(const super& a_rhs);
		TextInput(super&& a_rhs);

		~TextInput() = default;

		TextInput& operator=(const TextInput&) = default;
		TextInput& operator=(TextInput&&) = default;
		TextInput& operator=(const super& a_rhs);
		TextInput& operator=(super&& a_rhs);

	public:
		// Properties
		bool        Disabled() const { return GetBoolean("disabled"); }
		void        Disabled(bool a_value) { SetBoolean("disabled", a_value); }
		bool        Editable() const { return GetBoolean("editable"); }
		void        Editable(bool a_value) { SetBoolean("editable", a_value); }
		std::string HTMLText() const { return GetString("htmlText"); }
		void        HTMLText(std::string_view a_value) { SetString("htmlText", a_value); }
		double      Length() const { return GetNumber("length"); }
		double      MaxChars() const { return GetNumber("maxChars"); }
		void        MaxChars(double a_value) { SetNumber("maxChars", a_value); }
		bool        Password() const { return GetBoolean("password"); }
		void        Password(bool a_value) { SetBoolean("password", a_value); }
		std::string Text() const { return GetString("text"); }
		void        Text(std::string_view a_value) { SetString("text", a_value); }
		std::string TextID() const { return GetString("textID"); }
		void        TextID(std::string_view a_value) { SetString("textID", a_value); }

	public:
		// Methods
		void        AppendHTML(std::string_view a_text);
		void        AppendText(std::string_view a_text);
		std::string ToString();
	};
}

#include "TextInput.inl"
