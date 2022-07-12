#pragma once

#include "Scaleform/MovieClip.hpp"

namespace SF::CLIK::GFx::Core
{
	class UIComponent :
		public MovieClip
	{
		using super = MovieClip;

	public:
		using super::super;
		using super::operator=;

		UIComponent() = default;
		UIComponent(const UIComponent&) = default;
		UIComponent(UIComponent&&) = default;
		UIComponent(const super& a_rhs);
		UIComponent(super&& a_rhs);

		~UIComponent() = default;

		UIComponent& operator=(const UIComponent&) = default;
		UIComponent& operator=(UIComponent&&) = default;
		UIComponent& operator=(const super& a_rhs);
		UIComponent& operator=(super&& a_rhs);

	public:
		// Properties
		bool   Disabled() const { return GetBoolean("disabled"); }
		void   Disabled(bool a_value) { SetBoolean("disabled", a_value); }
		bool   DisplayFocus() const { return GetBoolean("displayFocus"); }
		void   DisplayFocus(bool a_value) { SetBoolean("displayFocus", a_value); }
		double Focused() const { return GetNumber("focused"); }
		void   Focused(double a_value) { SetNumber("focused", a_value); }
		double Height() const { return GetNumber("height"); }
		void   Height(double a_value) { SetNumber("height", a_value); }
		bool   Visible() const { return GetBoolean("visible"); }
		void   Visible(bool a_value) { SetBoolean("visible", a_value); }
		double Width() const { return GetNumber("width"); }
		void   Width(double a_value) { SetNumber("width", a_value); }

	public:
		// Methods
		void        SetSize(double a_width, double a_height);
		void        Invalidate();
		void        ValidateNow();
		std::string ToString();
		void        DispatchEventToGame(Object& a_event);
	};
}

#include "UIComponent.inl"
