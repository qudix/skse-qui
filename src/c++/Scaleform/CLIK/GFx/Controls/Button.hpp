#pragma once

#include "Scaleform/CLIK/GFx/Core/UIComponent.hpp"

namespace SF::CLIK::GFx::Controls
{
	class Button :
		public Core::UIComponent
	{
		using super = Core::UIComponent;

	public:
		using super::super;
		using super::operator=;

		Button() = default;
		Button(const Button&) = default;
		Button(Button&&) = default;
		Button(const super& a_rhs);
		Button(super&& a_rhs);

		~Button() = default;

		Button& operator=(const Button&) = default;
		Button& operator=(Button&&) = default;
		Button& operator=(const super& a_rhs);
		Button& operator=(super&& a_rhs);

	public:
		// Properties
		std::string AutoSize() const { return GetString("autoSize"); }
		void        AutoSize(std::string_view a_autoSize) { SetString("autoSize", a_autoSize); }
		bool        DisableConstraints() const { return GetBoolean("disableConstraints"); }
		void        DisableConstraints(bool a_disableConstraints) { SetBoolean("disableConstraints", a_disableConstraints); }
		bool        Disabled() const { return GetBoolean("disabled"); }
		void        Disabled(bool a_disabled) { SetBoolean("disabled", a_disabled); }
		bool        DisableFocus() const { return GetBoolean("disableFocus"); }
		void        DisableFocus(bool a_disableFocus) { SetBoolean("disableFocus", a_disableFocus); }
		Object      Group() const { return GetObject("group"); }
		void        Group(const Object& a_group) { SetObject("group", a_group); }
		std::string GroupName() const { return GetString("groupName"); }
		void        GroupName(std::string_view a_groupName) { SetString("groupName", a_groupName); }
		std::string Label() const { return GetString("label"); }
		void        Label(std::string_view a_label) { SetString("label", a_label); }
		std::string LabelID() const { return GetString("labelID"); }
		void        LabelID(std::string_view a_labelID) { SetString("labelID", a_labelID); }
		bool        Selected() const { return GetBoolean("selected"); }
		void        Selected(bool a_selected) { SetBoolean("selected", a_selected); }

	public:
		// Methods
		void        SetSize(double a_width, double a_height);
		std::string ToString();
	};
}

#include "Button.inl"
