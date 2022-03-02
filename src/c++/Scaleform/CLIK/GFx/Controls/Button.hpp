#pragma once

#include "Scaleform/CLIK/GFx/Core/UIComponent.hpp"

namespace CLIK::GFx::Controls
{
	class Button :
		public Core::UIComponent
	{
	private:
		using super = Core::UIComponent;

	public:
		Button() = default;
		Button(const Button&) = default;
		Button(Button&&) = default;
		using super::super;

		Button(const super& a_rhs) :
			super(a_rhs)
		{}

		Button(super&& a_rhs) :
			super(std::move(a_rhs))
		{}

		~Button() = default;

		Button& operator=(const Button&) = default;
		Button& operator=(Button&&) = default;
		using super::operator=;

		Button& operator=(const super& a_rhs)
		{
			super::operator=(a_rhs);
			return *this;
		}

		Button& operator=(super&& a_rhs)
		{
			super::operator=(std::move(a_rhs));
			return *this;
		}

		std::string LabelID() const { return GetString("labelID"); }
		void LabelID(std::string_view a_labelID) { SetString("labelID", a_labelID); }

		std::string Label() const { return GetString("label"); }
		void Label(std::string_view a_label) { SetString("label", a_label); }

		bool Disabled() const { return GetBoolean("disabled"); }
		void Disabled(bool a_disabled) { SetBoolean("disabled", a_disabled); }

		bool Selected() const { return GetBoolean("selected"); }
		void Selected(bool a_selected) { SetBoolean("selected", a_selected); }

		std::string GroupName() const { return GetString("groupName"); }
		void GroupName(std::string_view a_groupName) { SetString("groupName", a_groupName); }

		Object Group() const { return GetObject("group"); }
		void Group(const Object& a_group) { SetObject("group", a_group); }

		bool DisableFocus() const { return GetBoolean("disableFocus"); }
		void DisableFocus(bool a_disableFocus) { SetBoolean("disableFocus", a_disableFocus); }

		bool DisableConstraints() const { return GetBoolean("disableConstraints"); }
		void DisableConstraints(bool a_disableConstraints) { SetBoolean("disableConstraints", a_disableConstraints); }

		std::string AutoSize() const { return GetString("autoSize"); }
		void AutoSize(std::string_view a_autoSize) { SetString("autoSize", a_autoSize); }

		void SetSize(double a_width, double a_height)
		{
			enum
			{
				kWidth,
				kHeight,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kWidth] = a_width;
			assert(args[kWidth].IsNumber());

			args[kHeight] = a_height;
			assert(args[kHeight].IsNumber());

			[[maybe_unused]] const auto success =
				Invoke("setSize", nullptr, args.data(), args.size());
			assert(success);
		}

		//bool HandleInput(InputDetails& a_details, Array& a_pathToFocus);

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
