#pragma once

#include "Scaleform/CLIK/GFx/Core/UIComponent.hpp"

namespace CLIK
{
	namespace GFx
	{
		namespace Controls
		{
			class ButtonBar :
				public Core::UIComponent
			{
			private:
				using super = Core::UIComponent;

			public:
				ButtonBar() = default;
				ButtonBar(const ButtonBar&) = default;
				ButtonBar(ButtonBar&&) = default;
				using super::super;

				ButtonBar(const super& a_rhs) :
					super(a_rhs)
				{}

				ButtonBar(super&& a_rhs) :
					super(std::move(a_rhs))
				{}

				~ButtonBar() = default;

				ButtonBar& operator=(const ButtonBar&) = default;
				ButtonBar& operator=(ButtonBar&&) = default;
				using super::operator=;

				ButtonBar& operator=(const super& a_rhs)
				{
					super::operator=(a_rhs);
					return *this;
				}

				ButtonBar& operator=(super&& a_rhs)
				{
					super::operator=(std::move(a_rhs));
					return *this;
				}

				bool Disabled() { return GetBoolean("disabled"); }
				void Disabled(bool a_value) { return SetBoolean("disabled", a_value); }

				Object DataProvider() { return GetObject("dataProvider"); }
				void DataProvider(const Object& a_value) { return SetObject("dataProvider", a_value); }

				void InvalidateData()
				{
					[[maybe_unused]] const auto success =
						Invoke("invalidateData");
					assert(success);
				}

				std::string ItemRenderer() { return GetString("itemRenderer"); }
				void ItemRenderer(std::string_view a_value) { return SetString("itemRenderer", std::move(a_value)); }

				double Spacing() { return GetNumber("spacing"); }
				void Spacing(double a_value) { return SetNumber("spacing", a_value); }

				std::string Direction() { return GetString("direction"); }
				void Direction(std::string_view a_value) { return SetString("direction", a_value); }

				std::string AutoSize() { return GetString("autoSize"); }
				void AutoSize(std::string_view a_value) { return SetString("autoSize", a_value); }

				double ButtonWidth() { return GetNumber("buttonWidth"); }
				void ButtonWidth(double a_value) { return SetNumber("buttonWidth", a_value); }

				double SelectedIndex() { return GetNumber("selectedIndex"); }
				void SelectedIndex(double a_value) { return SetNumber("selectedIndex", a_value); }

				Object SelectedItem() { return GetObject("selectedItem"); }

				Object Data() { return GetObject("data"); }

				std::string LabelField() { return GetString("labelField"); }
				void LabelField(std::string_view a_value) { return SetString("labelField", a_value); }

				// CLIK::Function LabelFunction() { return GetObject("labelFunction"); }
				// void LabelFunction(CLIK::Function a_value) { return SetObject("labelFunction", a_value); }

				std::string ItemToLabel(Object a_item)
				{
					enum
					{
						kItem,
						kNumArgs
					};

					std::array<RE::GFxValue, kNumArgs> args;

					args[kItem] = a_item.GetInstance();
					assert(args[kItem].IsObject());

					RE::GFxValue str;
					[[maybe_unused]] const auto success =
						Invoke("itemToLabel", std::addressof(str), args.data(), args.size());
					assert(success);

					return str.GetString();
				}

				//bool handleInput(CLIK::GFx::UI::InputDetails a_details, CLIK::Array a_pathToFocus);

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
