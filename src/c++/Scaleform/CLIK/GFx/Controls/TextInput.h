#pragma once

#include "Scaleform/CLIK/GFx/Core/UIComponent.h"

namespace CLIK
{
	namespace GFx
	{
		namespace Controls
		{
			class TextInput :
				public Core::UIComponent
			{
			private:
				using super = Core::UIComponent;

			public:
				TextInput() = default;
				TextInput(const TextInput&) = default;
				TextInput(TextInput&&) = default;
				using super::super;

				TextInput(const super& a_rhs) :
					super(a_rhs)
				{}

				TextInput(super&& a_rhs) :
					super(std::move(a_rhs))
				{}

				~TextInput() = default;

				TextInput& operator=(const TextInput&) = default;
				TextInput& operator=(TextInput&&) = default;
				using super::operator=;

				TextInput& operator=(const super& a_rhs)
				{
					super::operator=(a_rhs);
					return *this;
				}

				TextInput& operator=(super&& a_rhs)
				{
					super::operator=(std::move(a_rhs));
					return *this;
				}

				std::string TextID() const { return GetString("textID"); }
				void TextID(std::string_view a_textID) { SetString("textID", a_textID); }

				std::string Text() const { return GetString("text"); }
				void Text(std::string_view a_text) { SetString("text", a_text); }

				std::string HTMLText() const { return GetString("htmlText"); }
				void HTMLText(std::string_view a_htmlText) { SetString("htmlText", a_htmlText); }

				bool Editable() const { return GetBoolean("editable"); }
				void Editable(bool a_editable) { SetBoolean("editable", a_editable); }

				bool Password() const { return GetBoolean("password"); }
				void Password(bool a_password) { SetBoolean("password", a_password); }

				double MaxChars() const { return GetNumber("maxChars"); }
				void MaxChars(double a_maxChars) { SetNumber("maxChars", a_maxChars); }

				bool Disabled() const { return GetBoolean("disabled"); }
				void Disabled(bool a_disabled) { SetBoolean("disabled", a_disabled); }

				void AppendText(std::string_view a_text)
				{
					enum
					{
						kText,
						kNumArgs
					};

					std::array<RE::GFxValue, kNumArgs> args;

					args[kText] = a_text;
					assert(args[kText].IsString());

					[[maybe_unused]] const auto success =
						Invoke("appendText", nullptr, args.data(), args.size());
					assert(success);
				}

				void AppendHTML(std::string_view a_text)
				{
					enum
					{
						kText,
						kNumArgs
					};

					std::array<RE::GFxValue, kNumArgs> args;

					args[kText] = a_text;
					assert(args[kText].IsString());

					[[maybe_unused]] const auto success =
						Invoke("appendHtml", nullptr, args.data(), args.size());
					assert(success);
				}

				double Length() const
				{
					return GetNumber("length");
				}

				//bool handleInput(InputDetails& a_details, Array& a_pathToFocus);

				std::string ToString()
				{
					RE::GFxValue str;
					[[maybe_unused]] const auto success =
						Invoke("toString", std::addressof(str));
					assert(success);
					return str.GetString();
				}
			};
		}
	}
}
