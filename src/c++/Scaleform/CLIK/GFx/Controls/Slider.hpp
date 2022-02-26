#pragma once

#include "Scaleform/CLIK/GFx/Core/UIComponent.hpp"

namespace CLIK
{
	namespace GFx
	{
		namespace Controls
		{
			class Slider : public Core::UIComponent
			{
			private:
				using super = Core::UIComponent;

			public:
				Slider() = default;
				Slider(const Slider&) = default;
				Slider(Slider&&) = default;
				using super::super;

				Slider(const super& a_rhs) :
					super(a_rhs)
				{}

				Slider(super&& a_rhs) :
					super(std::move(a_rhs))
				{}

				~Slider() = default;

				Slider& operator=(const Slider&) = default;
				Slider& operator=(Slider&&) = default;
				using super::operator=;

				Slider& operator=(const super& a_rhs)
				{
					super::operator=(a_rhs);
					return *this;
				}

				Slider& operator=(super&& a_rhs)
				{
					super::operator=(std::move(a_rhs));
					return *this;
				}

				double Maximum() const { return GetNumber("maximum"); }
				void Maximum(double a_maximum) { SetNumber("maximum", a_maximum); }

				double Minimum() const { return GetNumber("minimum"); }
				void Minimum(double a_minimum) { SetNumber("minimum", a_minimum); }

				double Value() const { return GetNumber("value"); }
				void Value(double a_value) { SetNumber("value", a_value); }

				bool Disabled() const { return GetBoolean("disabled"); }
				void Disabled(bool a_disabled) { SetBoolean("disabled", a_disabled); }

				double Position() const { return GetNumber("position"); }
				void Position(double a_position) { SetNumber("position", a_position); }

				bool Snapping() const { return GetBoolean("snapping"); }
				void Snapping(bool a_snapping) { SetBoolean("snapping", a_snapping); }

				double SnapInterval() const { return GetNumber("snapInterval"); }
				void SnapInterval(double a_snapInterval) { SetNumber("snapInterval", a_snapInterval); }

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
	}
}
