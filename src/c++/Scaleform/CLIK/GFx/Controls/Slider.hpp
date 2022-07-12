#pragma once

#include "Scaleform/CLIK/GFx/Core/UIComponent.hpp"

namespace SF::CLIK::GFx::Controls
{
	class Slider :
		public Core::UIComponent
	{
		using super = Core::UIComponent;

	public:
		using super::super;
		using super::operator=;

		Slider() = default;
		Slider(const Slider&) = default;
		Slider(Slider&&) = default;

		~Slider() = default;

		Slider& operator=(const Slider&) = default;
		Slider& operator=(Slider&&) = default;
		Slider& operator=(const super& a_rhs);
		Slider& operator=(super&& a_rhs);

	public:
		// Properties
		bool   Disabled() const { return GetBoolean("disabled"); }
		void   Disabled(bool a_value) { SetBoolean("disabled", a_value); }
		double Maximum() const { return GetNumber("maximum"); }
		void   Maximum(double a_value) { SetNumber("maximum", a_value); }
		double Minimum() const { return GetNumber("minimum"); }
		void   Minimum(double a_value) { SetNumber("minimum", a_value); }
		double Position() const { return GetNumber("position"); }
		void   Position(double a_value) { SetNumber("position", a_value); }
		double SnapInterval() const { return GetNumber("snapInterval"); }
		void   SnapInterval(double a_value) { SetNumber("snapInterval", a_value); }
		bool   Snapping() const { return GetBoolean("snapping"); }
		void   Snapping(bool a_value) { SetBoolean("snapping", a_value); }
		double Value() const { return GetNumber("value"); }
		void   Value(double a_value) { SetNumber("value", a_value); }

	public:
		// Methods
		std::string ToString();
	};
}

#include "Slider.inl"
